// No Copyright.

#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Move,
		"Input.Move",
		"Input tag for character's movement"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_LMB,
		"Input.LMB",
		"Input tag for left mouse button"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_RMB,
		"Input.RMB",
		"Input tag for right mouse button"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_1,
		"Input.1",
		"Input tag for 1 Key on keyboard"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_2,
		"Input.2",
		"Input tag for 2 Key on keyboard"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_3,
		"Input.3",
		"Input tag for 3 Key on keyboard"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_4,
		"Input.4",
		"Input tag for 4 Key on keyboard"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Input_Shift,
		"Input.Shift",
		"Input tag for Shift Key on keyboard"
	);
	
	/** Primary Attribute Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Primary_Strength,
		"Attribute.Primary.Strength",
		"Attribute tag for character's strength"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Primary_Intelligence,
		"Attribute.Primary.Intelligence",
		"Attribute tag for character's intelligence"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Primary_Resilience,
		"Attribute.Primary.Resilience",
		"Attribute tag for character's resilience"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Primary_Vigor,
		"Attribute.Primary.Vigor",
		"Attribute tag for character's vigor"
	);
	
	/** Secondary Attribute Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_Armor,
		"Attribute.Secondary.Armor",
		"Attribute tag for character's armor"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_ArmorPenetration,
		"Attribute.Secondary.ArmorPenetration",
		"Attribute tag for character's armor penetration"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_CriticalHitChance,
		"Attribute.Secondary.CriticalHitChance",
		"Attribute tag for character's critical hit chance"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_CriticalHitDamage,
		"Attribute.Secondary.CriticalHitDamage",
		"Attribute tag for character's critical hit damage"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_CriticalHitResistance,
		"Attribute.Secondary.CriticalHitResistance",
		"Attribute tag for character's critical hit resistance"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_BlockChance,
		"Attribute.Secondary.BlockChance",
		"Attribute tag for character's block chance"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_HealthRegeneration,
		"Attribute.Secondary.HealthRegeneration",
		"Attribute tag for character's health regeneration"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_ManaRegeneration,
		"Attribute.Secondary.ManaRegeneration",
		"Attribute tag for character's mana regeneration"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_MaxHealth,
		"Attribute.Secondary.MaxHealth",
		"Attribute tag for character's maximum health"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Secondary_MaxMana,
		"Attribute.Secondary.MaxMana",
		"Attribute tag for character's maximum mana"
	);
	
	/** Vital Attribute Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Vital_Health,
		"Attribute.Vital.Health",
		"Attribute tag for character's health"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Vital_Mana,
		"Attribute.Vital.Mana",
		"Attribute tag for character's mana"
	);
	
	/** Meta-Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Attribute_Meta_Damage,
		"Attribute.Meta.Damage",
		"Attribute tag for damage inflicted by abilities"
	);
	
	/** Ability Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Ability_HitReact,
		"Ability.HitReact",
		"Ability tag granted when hit reacting"
	);
	
	/** Effect Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Effect_HitReact,
		"Effect.HitReact",
		"Effect tag granted when hit reacting"
	);
	
	/** Event Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Event_Montage_FireBolt,
		"Event.Montage.FireBolt", 
		"Event tag for character's FireBolt Ability"
	);
	
	/** Message Tags **/
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Message_Potion_Health,
		"Message.Potion.Health",
		"Message tag for health potion to restore character's health"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Message_Potion_Mana,
		"Message.Potion.Mana",
		"Message tag for mana potion to restore character's mana"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Message_Crystal_Health,
		"Message.Crystal.Health",
		"Message tag for health crystal to restore character's health"
	);
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT
	(
		Message_Crystal_Mana,
		"Message.Crystal.Mana",
		"Message tag for mana crystal to restore character's mana"
	);
}
