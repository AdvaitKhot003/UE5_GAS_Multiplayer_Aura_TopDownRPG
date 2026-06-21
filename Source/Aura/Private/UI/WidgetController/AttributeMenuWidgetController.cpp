// No Copyright.

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AuraAttributeInfoConfig.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfoConfig);
	UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	check(AuraAttributeSet);
	
	for (auto& Pair : AuraAttributeSet->AttributeTagsToAttributes)
	{
		FAuraAttributeInfo AttributeInfo = AttributeInfoConfig->FindAttributeInfoByTag(Pair.Key);
		if (!AttributeInfo.IsValid()) continue;
		AttributeInfo.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
		AttributeInfoDelegate.Broadcast(AttributeInfo);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}
