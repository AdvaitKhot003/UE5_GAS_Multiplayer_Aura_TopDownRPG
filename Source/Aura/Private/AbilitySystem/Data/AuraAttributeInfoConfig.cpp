// No Copyright.

#include "AbilitySystem/Data/AuraAttributeInfoConfig.h"

FAuraAttributeInfo UAuraAttributeInfoConfig::FindAttributeInfoByTag(const FGameplayTag& InAttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& AttributeInfoConfig : AttributeInfos)
	{
		if (AttributeInfoConfig.IsValid() && AttributeInfoConfig.AttributeTag.MatchesTagExact(InAttributeTag))
		{
			return AttributeInfoConfig;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Could not find AttributeInfo for AttributeTag: [%s] on AttributeInfoConfig: [%s]"),
			*InAttributeTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAttributeInfo();
}
