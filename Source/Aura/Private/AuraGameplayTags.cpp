// No Copyright.

#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Move, "Input.Move",
		"Input tag for character's movement");
	
	/** Vital Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Health, "Attribute.Vital.Health",
		"Attribute tag for character's health");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Mana, "Attribute.Vital.Mana",
		"Attribute tag for character's mana");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_MaxHealth, "Attribute.Vital.MaxHealth",
		"Attribute tag for character's maximum health");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_MaxMana, "Attribute.Vital.MaxMana",
		"Attribute tag for character's maximum mana");
	
	/** Primary Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Strength, "Attribute.Primary.Strength",
		"Attribute tag for character's strength");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Intelligence, "Attribute.Primary.Intelligence",
		"Attribute tag for character's intelligence");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Resilience, "Attribute.Primary.Resilience",
		"Attribute tag for character's resilience");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Vigor, "Attribute.Primary.Vigor",
		"Attribute tag for character's vigor");
	
	/** Message Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Potion_Health, "Message.Potion.Health",
		"Message tag for health potion to restore character's health");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Potion_Mana, "Message.Potion.Mana",
		"Message tag for mana potion to restore character's mana");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Crystal_Health, "Message.Crystal.Health",
		"Message tag for health crystal to restore character's health");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Message_Crystal_Mana, "Message.Crystal.Mana",
		"Message tag for mana crystal to restore character's mana");
}
