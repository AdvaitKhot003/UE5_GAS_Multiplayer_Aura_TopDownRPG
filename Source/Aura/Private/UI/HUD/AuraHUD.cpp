// No Copyright.

#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/UserWidget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	
	OverlayWidget = CastChecked<UAuraUserWidget>(
		CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass));
	
	OverlayWidget->AddToViewport();
}
