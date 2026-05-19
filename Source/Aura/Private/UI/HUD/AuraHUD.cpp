// No Copyright.

#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/UserWidget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* Pc, APlayerState* Ps, UAbilitySystemComponent* Asc, UAttributeSet* As)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);
	
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = CastChecked<UAuraUserWidget>(UserWidget);
	
	const FWidgetControllerParams Params(Pc, Ps, Asc, As);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}
