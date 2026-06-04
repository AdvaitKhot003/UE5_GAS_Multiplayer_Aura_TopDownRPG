// No Copyright.

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Move);
	
	/** Vital Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxHealth);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_MaxMana);
	
	/** Primary Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Strength);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Intelligence);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Resilience);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Vigor);
	
	/** Message Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Potion_Mana);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Crystal_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Crystal_Mana);
}
