// No Copyright.

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AuraAttributeInfoConfig.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfoConfig);
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	
	FAuraAttributeInfo AttributeInfo = AttributeInfoConfig->FindAttributeInfoByTag(AuraGameplayTags::Attribute_Primary_Strength);
	if (!AttributeInfo.IsValid()) return;
	AttributeInfo.AttributeValue = AuraAttributeSet->GetStrength();
	AttributeInfoDelegate.Broadcast(AttributeInfo);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}
