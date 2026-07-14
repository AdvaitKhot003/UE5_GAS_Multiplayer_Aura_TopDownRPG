// No Copyright.

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "Game/AuraGameModeBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"

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

void UAuraAbilitySystemLibrary::InitDefaultAttributesByLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass,
	float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	const AAuraGameModeBase* AuraGameMode =
		Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));

	if (!AuraGameMode || !AbilitySystemComponent) return;

	const FCharacterClassDefaultInfo ClassDefaultInfo =
		AuraGameMode->CharacterClassInfo->FindCharacterClassDefaultInfo(CharacterClass);

	auto ApplyEffect = [&](TSubclassOf<UGameplayEffect> GameplayEffectClass)
	{
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(AbilitySystemComponent->GetAvatarActor());

		const FGameplayEffectSpecHandle SpecHandle =
			AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);

		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	};

	ApplyEffect(ClassDefaultInfo.PrimaryAttributes);
	ApplyEffect(AuraGameMode->CharacterClassInfo->SecondaryAttributes);
	ApplyEffect(AuraGameMode->CharacterClassInfo->VitalAttributes);
}

void UAuraAbilitySystemLibrary::GiveStartUpAbilities(
	const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode || !AbilitySystemComponent) return;
	
	const UCharacterClassInfoConfig* CharacterClassInfoConfig = AuraGameMode->CharacterClassInfo;
	for (const TSubclassOf<UAuraGameplayAbility>& AbilityClass : CharacterClassInfoConfig->SharedAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.Level = 1.f;
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}
