// No Copyright.

#include "EnhancedInput/AuraInputConfig.h"

UInputAction* UAuraInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound) const
{
	for (const FAuraInputActionConfig& Config : NativeInputActions)
	{
		if (Config.IsValid() && Config.InputTag == InInputTag)
		{
			return Config.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Could not find NativeInputAction for InputTag: [%s] on InputConfig: [%s]"),
			*InInputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
