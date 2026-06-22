// No Copyright.

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityCharacterInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);
	EffectAssetTagsDelegate.Broadcast(AssetTags);
}

void UAuraAbilitySystemComponent::GrantCharacterStartUpAbilities(
	const TArray<TSubclassOf<UAuraGameplayAbility>>& GameplayAbilities, float AbilityLevel)
{
	for (const TSubclassOf<UAuraGameplayAbility>& AbilityClass : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.Level = AbilityLevel;
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}
