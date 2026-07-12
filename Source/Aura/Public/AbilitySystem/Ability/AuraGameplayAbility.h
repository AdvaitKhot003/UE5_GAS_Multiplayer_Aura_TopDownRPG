// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Input")
	FGameplayTag StartUpAbilityInputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Damage")
	FScalableFloat Damage = 10.f;
};
