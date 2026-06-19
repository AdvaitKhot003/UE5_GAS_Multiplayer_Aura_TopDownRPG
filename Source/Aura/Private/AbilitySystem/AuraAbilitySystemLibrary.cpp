// No Copyright.

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AAuraHUD* AuraHUD = nullptr;
	if (!MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, AuraHUD)) return nullptr;
	return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WidgetControllerParams;
	AAuraHUD* AuraHUD = nullptr;
	if (!MakeWidgetControllerParams(WorldContextObject, WidgetControllerParams, AuraHUD)) return nullptr;
	return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
}

bool UAuraAbilitySystemLibrary::MakeWidgetControllerParams(
	const UObject* WorldContextObject, FWidgetControllerParams& OutWidgetControllerParams, AAuraHUD*& OutAuraHUD)
{
	APlayerController* LocalPc = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!LocalPc) return false;
	
	AAuraPlayerState* AuraPs = LocalPc->GetPlayerState<AAuraPlayerState>();
	if (!AuraPs) return false;
	
	UAbilitySystemComponent* Asc = AuraPs->GetAbilitySystemComponent();
	if (!Asc) return false;
	
	UAttributeSet* As = AuraPs->GetAttributeSet();
	if (!As) return false;
	
	OutAuraHUD = Cast<AAuraHUD>(LocalPc->GetHUD());
	if (!OutAuraHUD) return false;
	
	const FWidgetControllerParams WidgetControllerParams(LocalPc, AuraPs, Asc, As);
	OutWidgetControllerParams = WidgetControllerParams;
	return true;
}
