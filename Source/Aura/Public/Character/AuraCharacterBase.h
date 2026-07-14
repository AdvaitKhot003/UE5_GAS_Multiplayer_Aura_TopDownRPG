// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAnimMontage;
class UMotionWarpingComponent;
class UAuraGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual void BeginPlay() override;
	
	/** Ability System Interface - Start **/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/** Ability System Interface - End **/
	
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
	
	/** Combat Interface - Start **/
	virtual FVector GetCombatSocketLocation() const override;
	virtual void UpdateWarpTarget(const FVector& TargetLocation) const override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() const override;
	/** Combat Interface - End **/
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName WeaponTipSocket;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityCharacterInfo();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level = 1.f);
	virtual void InitDefaultAttributes();
	
	void GiveCharacterStartUpAbilities();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbilities", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<UAuraGameplayAbility>> StartUpGameplayAbilities;
};
