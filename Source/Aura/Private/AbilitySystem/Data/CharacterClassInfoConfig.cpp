// No Copyright.

#include "AbilitySystem/Data/CharacterClassInfoConfig.h"

FCharacterClassDefaultInfo UCharacterClassInfoConfig::FindCharacterClassDefaultInfo(ECharacterClass CharacterClass) const
{
	return CharacterClassDefaultInfo.FindChecked(CharacterClass);
}
