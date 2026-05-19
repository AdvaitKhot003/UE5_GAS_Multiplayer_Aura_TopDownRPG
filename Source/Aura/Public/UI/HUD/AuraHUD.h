// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	
	void InitOverlay(APlayerController* Pc, APlayerState* Ps, UAbilitySystemComponent* Asc, UAttributeSet* As);
	
protected:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = true))
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
