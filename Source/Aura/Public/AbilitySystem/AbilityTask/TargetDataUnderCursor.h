// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderCursor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataUnderCursorSignature,
	const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderCursor : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataUnderCursor* GetTargetDataUnderCursor(UGameplayAbility* OwningAbility);
	
	UPROPERTY(BlueprintAssignable, Category = "Ability|Tasks")
	FTargetDataUnderCursorSignature OnValidTargetData;
	
protected:
	virtual void Activate() override;
	
private:
	void SendTargetDataUnderCursor();
	void OnTargetDataReplicated(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ActivationTag);
};
