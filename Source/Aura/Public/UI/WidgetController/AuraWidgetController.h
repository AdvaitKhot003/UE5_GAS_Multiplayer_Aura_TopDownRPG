// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class APlayerState;
class APlayerController;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* Pc, APlayerState* Ps, UAbilitySystemComponent* Asc, UAttributeSet* As)
		: PlayerController(Pc), PlayerState(Ps), AbilitySystemComponent(Asc), AttributeSet(As) {}
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
