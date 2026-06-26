// No Copyright.

#include "AbilitySystem/AbilityTask/TargetDataUnderCursor.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::GetTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCursor* TargetDataUnderCursor = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);
	return TargetDataUnderCursor;
}

void UTargetDataUnderCursor::Activate()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo) return;

	const APlayerController* PlayerController = ActorInfo->PlayerController.Get();
	if (!PlayerController) return;
	
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	
	if (HitResult.IsValidBlockingHit())
	{
		OnValidTargetData.Broadcast(HitResult.ImpactPoint);
	}
}
