// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	AActor* SourceAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	AController* SourceController = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	AController* TargetController = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	/** Vital Attributes **/
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Attributes|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Health)
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Attributes|Vital")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxHealth)
	
	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Attributes|Vital")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Mana)
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Attributes|Vital")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxMana)
	
	/** Primary Attributes **/
	
	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Strength)
	
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Intelligence)
	
	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Resilience)
	
	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Vigor)
	
	/** Vital Attributes **/
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	/** Primary Attributes **/
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
