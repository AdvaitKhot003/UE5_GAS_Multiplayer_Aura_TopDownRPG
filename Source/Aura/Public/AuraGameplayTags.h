// No Copyright.

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_LMB);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_RMB);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_1);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_2);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_3);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_4);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Shift);
	
	/** Primary Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Strength);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Intelligence);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Resilience);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Vigor);
	
	/** Secondary Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_Armor);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_ArmorPenetration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitChance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitDamage);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_CriticalHitResistance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_BlockChance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_HealthRegeneration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_ManaRegeneration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxHealth);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxMana);
	
	/** Vital Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	
	/** Meta-Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Meta_Damage);
	
	/** Ability Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_HitReact);
	
	/** Effect Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_HitReact);
	
	/** Event Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_FireBolt);
	
	/** Message Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Mana);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Crystal_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Crystal_Mana);
}
