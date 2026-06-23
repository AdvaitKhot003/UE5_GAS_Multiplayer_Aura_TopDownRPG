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
		const UAuraGameplayAbility* AuraAbilityCDO = AbilityClass->GetDefaultObject<UAuraGameplayAbility>();
		if (!AuraAbilityCDO) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraAbilityCDO->StartUpAbilityInputTag);
		AbilitySpec.Level = AbilityLevel;
		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	
}

void UAuraAbilitySystemComponent::OnAbilityInputHeld(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		
		AbilitySpecInputPressed(AbilitySpec);

		if (AbilitySpec.IsActive())
		{
			const UGameplayAbility* AbilityInstance = AbilitySpec.GetPrimaryInstance();
			if (!AbilityInstance) continue;
			
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle,
				AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UAuraAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		
		AbilitySpecInputReleased(AbilitySpec);

		if (AbilitySpec.IsActive())
		{
			const UGameplayAbility* AbilityInstance = AbilitySpec.GetPrimaryInstance();
			if (!AbilityInstance) continue;
			
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle,
				AbilityInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
		}
	}
}
