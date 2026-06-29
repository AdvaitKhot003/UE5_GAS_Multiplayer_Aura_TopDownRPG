// No Copyright.

#include "AbilitySystem/AbilityTask/TargetDataUnderCursor.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::GetTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCursor* TargetDataUnderCursor = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);
	return TargetDataUnderCursor;
}

void UTargetDataUnderCursor::Activate()
{
	/*
	 * This AbilityTask has two execution paths:
	 *
	 * 1. Owning client
	 *    - Read the mouse cursor position.
	 *    - Send the target data to the server.
	 *    - Continue immediately using client-side prediction.
	 *
	 * 2. Server
	 *    - Wait until the owning client sends its cursor hit result.
	 *    - Resume execution once the replicated target data arrives.
	 */

	if (IsLocallyControlled())
	{
		/* We own the player, so gather cursor data locally. */
		SendTargetDataUnderCursor();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		/* Register a callback so GAS can notify us when the owning client sends its target data. */
		AbilitySystemComponent->AbilityTargetDataSetDelegate(
			SpecHandle,
			ActivationPredictionKey
		).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicated);
		
		/*
		 * The target data may have already arrived before we registered the delegate (race condition).
		 * If so, execute it immediately.
		 */
		const bool bCalledDelegate =
			AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		
		
		/* Otherwise, suspend this AbilityTask until the client provides its target data. */
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderCursor::SendTargetDataUnderCursor()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo) return;

	const APlayerController* PlayerController = ActorInfo->PlayerController.Get();
	if (!PlayerController) return;
	
	/*
	 * Opens a prediction window.
	 * GAS associates all predictions performed inside this scope with the current PredictionKey so the server can validate it.
	 */
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	FHitResult CursorHitResult;
	PlayerController->GetHitResultUnderCursor(
		ECC_Visibility,
		false,
		CursorHitResult
	);
	
	/* No valid cursor hit. */
	if (!CursorHitResult.bBlockingHit) return;
	
	/*
	 * Package the cursor hit into a GAS TargetDataHandle.
	 * TargetData is the standard way abilities exchange targeting information.
	 */
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetData->HitResult = CursorHitResult;
	TargetDataHandle.Add(TargetData);
	
	/*
	 * Send the cursor hit to the server.
	 * The server will receive this data and continue executing the ability using the exact same target information.
	 */
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetDataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
	);
	
	/* Broadcast immediately on the owning client, so predicted gameplay can continue without waiting for the server. */
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnValidTargetData.Broadcast(TargetDataHandle);
	}
}

void UTargetDataUnderCursor::OnTargetDataReplicated(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ActivationTag)
{
	/*
	 * The replicated target data has now been consumed.
	 * Remove it from the ASC so it isn't reused accidentally.
	 */
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	
	/* Continue ability execution using the replicated target data received from the owning client. */
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnValidTargetData.Broadcast(TargetDataHandle);
	}
}
