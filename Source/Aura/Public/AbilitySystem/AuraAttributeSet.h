// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

// DECLARE_DELEGATE_RetVal(FGameplayAttribute, FGameplayAttributeSignature);
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	TObjectPtr<AActor> SourceAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	TObjectPtr<AController> SourceController = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Source")
	TObjectPtr<ACharacter> SourceCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	TObjectPtr<AActor> TargetAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	TObjectPtr<AController> TargetController = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "EffectProperties|Target")
	TObjectPtr<ACharacter> TargetCharacter = nullptr;
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
	
	// TMap<FGameplayTag, FGameplayAttribute> AttributeTagsToAttributes;
	// TMap<FGameplayTag, FGameplayAttributeSignature> AttributeTagsToAttributes;
	// TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr or FGameplayAttribute(*)()
	// TMap<FGameplayTag, FGameplayAttribute(*)()> AttributeTagsToAttributes;
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> AttributeTagsToAttributes;
	
	/** Primary Attributes **/
	
	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Strength; /** Increases Physical Damage **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Strength)
	
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Intelligence;  /** Increases Magical Damage and Max Mana **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Intelligence)
	
	UPROPERTY(ReplicatedUsing = OnRep_Resilience, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Resilience;  /** Increases Armor and Armor Penetration **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Resilience)
	
	UPROPERTY(ReplicatedUsing = OnRep_Vigor, BlueprintReadOnly, Category = "Attributes|Primary")
	FGameplayAttributeData Vigor;  /** Increases Max Health and Health Regeneration **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Vigor)
	
	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	/** Secondary Attributes **/
	
	UPROPERTY(ReplicatedUsing = OnRep_Armor, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData Armor;  /** Reduces incoming damage and improves Block Chance [Resilience] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Armor)
	
	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData ArmorPenetration;  /** Ignores enemy Armor and improves Critical Hit Chance [Resilience] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ArmorPenetration)
	
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData CriticalHitChance;  /** Chance to deal with a critical strike [ArmorPenetration] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalHitChance)
	
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData CriticalHitDamage;  /** Additional damage dealt by critical strikes [ArmorPenetration] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalHitDamage)
	
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData CriticalHitResistance;  /** Reduces enemy critical hit chance [Armor] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalHitResistance)
	
	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData BlockChance;  /** Chance to reduce incoming damage by 50% [Armor] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, BlockChance)
	
	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData HealthRegeneration;  /** Health restored each second [Vigor] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, HealthRegeneration)
	
	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData ManaRegeneration;  /** Mana restored each second [Intelligence] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ManaRegeneration)
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData MaxHealth;  /** Maximum amount of Health obtainable [Vigor] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxHealth)
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana, BlueprintReadOnly, Category = "Attributes|Secondary")
	FGameplayAttributeData MaxMana;  /** Maximum amount of Mana obtainable [Intelligence] **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxMana)
	
	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION() void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION() void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION() void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION() void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION() void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION() void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	/** Vital Attributes **/
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Attributes|Vital")
	FGameplayAttributeData Health;  /** Current amount of Health. If it reaches zero, the character dies **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Health)
	
	UPROPERTY(ReplicatedUsing = OnRep_Mana, BlueprintReadOnly, Category = "Attributes|Vital")
	FGameplayAttributeData Mana;  /** Current amount of Mana available for abilities **/
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Mana)
	
	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
