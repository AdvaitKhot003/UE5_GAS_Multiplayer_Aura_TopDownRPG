// No Copyright.

#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AuraGameplayTags.h"
#include "Interaction/CombatInterface.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	/** Primary Attributes **/
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Primary_Strength, GetStrengthAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Primary_Resilience, GetResilienceAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Primary_Vigor, GetVigorAttribute);
	
	/** Secondary Attributes **/
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_Armor, GetArmorAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_MaxHealth, GetMaxHealthAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Secondary_MaxMana, GetMaxManaAttribute);
	
	/** Vital Attributes **/
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Vital_Health, GetHealthAttribute);
	AttributeTagsToAttributes.Add(AuraGameplayTags::Attribute_Vital_Mana, GetManaAttribute);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	/** Primary Attributes **/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always)
	
	/** Secondary Attributes **/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
	
	/** Vital Attributes **/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always)
}

/** Primary Attributes **/

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength)
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence)
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience)
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor)
}

/** Secondary Attributes **/

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor)
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration)
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance)
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage)
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance)
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance)
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration)
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration)
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth)
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana)
}

/** Vital Attributes **/

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth)
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana)
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		
		UE_LOG(LogTemp, Warning,
			TEXT("AvatarActorName: %s AvatarActorHealth: %f"),
			*Props.TargetAvatarActor->GetActorNameOrLabel(), GetHealth());
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = FMath::Clamp(GetHealth() - LocalIncomingDamage, 0.f, GetMaxHealth());
			SetHealth(NewHealth);
			
			UE_LOG(LogTemp, Warning,
				TEXT("AvatarActorName: %s AvatarActorHealth: %f"),
				*Props.TargetAvatarActor->GetActorNameOrLabel(), GetHealth());
			
			const bool bIsDead = NewHealth <= 0.f;
			if (!bIsDead)
			{
				FGameplayTagContainer Tags;
				Tags.AddTag(AuraGameplayTags::Ability_HitReact);
				Props.TargetAbilitySystemComponent->TryActivateAbilitiesByTag(Tags);
			}
			else
			{
				if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor))
				{
					CombatInterface->Die();
				}
			}
		}
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Cache Effect context Handle
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	AActor* Causer = Props.EffectContextHandle.GetEffectCauser();
	AActor* InstigatorActor = Props.EffectContextHandle.GetInstigator();

	/** SOURCE (Instigator + Effect Causer) **/
	
	// Source Ability System Component
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetInstigatorAbilitySystemComponent();

	// Source Avatar Actor
	if (Props.SourceAbilitySystemComponent)
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->GetAvatarActor();
	}
	else if (Causer)
	{
		Props.SourceAvatarActor = Causer;
	}
	else
	{
		Props.SourceAvatarActor = InstigatorActor;
	}
	
	// Source Controller
	if (const APawn* SourcePawn = Cast<APawn>(Props.SourceAvatarActor))
	{
		Props.SourceController = SourcePawn->GetController();
	}
	
	if (!Props.SourceController && InstigatorActor)
	{
		if (const APawn* InstigatorPawn = Cast<APawn>(InstigatorActor))
		{
			Props.SourceController = InstigatorPawn->GetController();
		}
	}

	// Source Character
	Props.SourceCharacter = Cast<ACharacter>(Props.SourceAvatarActor);

	if (!Props.SourceCharacter && Props.SourceController)
	{
		Props.SourceCharacter = Props.SourceController->GetCharacter();
	}

	/** TARGET (AttributeSet Owner) **/

	// Target Ability System Component
	Props.TargetAbilitySystemComponent = GetOwningAbilitySystemComponent();

	// Target Avatar Actor
	Props.TargetAvatarActor = Props.TargetAbilitySystemComponent ?
		Props.TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	// Target Controller
	if (const APawn* TargetPawn = Cast<APawn>(Props.TargetAvatarActor))
	{
		Props.TargetController = TargetPawn->GetController();
	}

	// Target Character
	Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

	if (!Props.TargetCharacter && Props.TargetController)
	{
		Props.TargetCharacter = Props.TargetController->GetCharacter();
	}
}
