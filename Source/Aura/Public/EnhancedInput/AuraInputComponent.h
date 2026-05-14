// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class UserObject, typename CallbackFunction>
	void BindNativeInputAction(const UAuraInputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function);
	
	template <class UserObject, typename CallbackFunction>
	void BindAbilityInputAction(const UAuraInputConfig* InInputConfig, UserObject* ContextObject,
		CallbackFunction InputPressedFunction, CallbackFunction InputHeldFunction, CallbackFunction InputReleasedFunction);
	
};

template <class UserObject, typename CallbackFunction>
void UAuraInputComponent::BindNativeInputAction(const UAuraInputConfig* InInputConfig, const FGameplayTag& InInputTag,
	ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function)
{
	checkf(InInputConfig, TEXT("InInputConfig is null on AuraInputComponent [%s]"), *GetNameSafe(this));
	
	if (UInputAction* InputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(InputAction, TriggerEvent, ContextObject, Function);
	}
}

template <class UserObject, typename CallbackFunction>
void UAuraInputComponent::BindAbilityInputAction(const UAuraInputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunction InputPressedFunction, CallbackFunction InputHeldFunction, CallbackFunction InputReleasedFunction)
{
	checkf(InInputConfig, TEXT("InInputConfig is null on AuraInputComponent [%s]"), *GetNameSafe(this));
	
	for (const FAuraInputActionConfig& Config : InInputConfig->AbilityInputActions)
	{
		if (!Config.IsValid()) continue;
		
		if (InputPressedFunction)
		{
			BindAction(Config.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunction, Config.InputTag);
		}
		
		if (InputHeldFunction)
		{
			BindAction(Config.InputAction, ETriggerEvent::Triggered, ContextObject, InputHeldFunction, Config.InputTag);
		}
		
		if (InputReleasedFunction)
		{
			BindAction(Config.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunction, Config.InputTag);
		}
	}
}
