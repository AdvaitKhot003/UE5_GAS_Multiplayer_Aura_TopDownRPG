// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class UAuraGameplayAbility;
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityCharacterInfoSet();
	
	void GiveCharacterStartUpAbilities(
		const TArray<TSubclassOf<UAuraGameplayAbility>>& GameplayAbilities, float AbilityLevel = 1.f);
	
	FEffectAssetTags EffectAssetTagsDelegate;
	
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputHeld(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
	
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveEffectHandle);
};
