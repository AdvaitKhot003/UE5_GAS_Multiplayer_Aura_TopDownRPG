// No Copyright.

#include "EnhancedInput/AuraInputConfig.h"

UInputAction* UAuraInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound) const
{
	for (const FAuraInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.IsValid() && InputActionConfig.InputTag.MatchesTagExact(InInputTag))
		{
			return InputActionConfig.InputAction;
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

UInputAction* UAuraInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound) const
{
	for (const FAuraInputActionConfig& InputActionConfig : AbilityInputActions)
	{
		if (InputActionConfig.IsValid() && InputActionConfig.InputTag.MatchesTagExact(InInputTag))
		{
			return InputActionConfig.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Could not find AbilityInputAction for InputTag: [%s] on InputConfig: [%s]"),
			*InInputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
