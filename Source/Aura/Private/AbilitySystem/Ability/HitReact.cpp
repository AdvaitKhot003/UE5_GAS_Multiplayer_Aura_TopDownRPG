// No Copyright.

#include "AbilitySystem/Ability/HitReact.h"

void UHitReact::ApplyHitReactGameplayEffectToOwner()
{
	check(HitReactEffectClass);

	const UGameplayEffect* HitReactEffect = HitReactEffectClass->GetDefaultObject<UGameplayEffect>();

	HitReactActiveEffectHandle = ApplyGameplayEffectToOwner(
		CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, HitReactEffect, GetAbilityLevel());
}
