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
	if (IsLocallyControlled())
	{
		SendTargetDataUnderCursor();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent->AbilityTargetDataSetDelegate(
			SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicated);
		
		const bool bCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(
			SpecHandle, ActivationPredictionKey);
		
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
	
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	FHitResult CursorHitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
	
	if (!CursorHitResult.bBlockingHit) return;
	
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetData->HitResult = CursorHitResult;
	TargetDataHandle.Add(TargetData);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetDataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey
	);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnValidTargetData.Broadcast(TargetDataHandle);
	}
}

void UTargetDataUnderCursor::OnTargetDataReplicated(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
    
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnValidTargetData.Broadcast(TargetDataHandle);
	}
}
