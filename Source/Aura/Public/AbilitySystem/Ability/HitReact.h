// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "HitReact.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURA_API UHitReact : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Ability|HitReact")
	void ApplyHitReactGameplayEffectToOwner();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|HitReact")
	TSubclassOf<UGameplayEffect> HitReactEffectClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "Ability|HitReact")
	FActiveGameplayEffectHandle HitReactActiveEffectHandle;
};
