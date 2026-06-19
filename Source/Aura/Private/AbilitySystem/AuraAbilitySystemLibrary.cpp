// No Copyright.

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* LocalPc = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!LocalPc) return nullptr;

	AAuraPlayerState* AuraPs = LocalPc->GetPlayerState<AAuraPlayerState>();
	if (!AuraPs) return nullptr;

	UAbilitySystemComponent* Asc = AuraPs->GetAbilitySystemComponent();
	check(Asc);

	UAttributeSet* As = AuraPs->GetAttributeSet();
	check(As);
	
	AAuraHUD* AuraHUD = Cast<AAuraHUD>(LocalPc->GetHUD());
	if (!AuraHUD) return nullptr;

	const FWidgetControllerParams Params(LocalPc, AuraPs, Asc, As);
	return AuraHUD->GetOverlayWidgetController(Params);
}
