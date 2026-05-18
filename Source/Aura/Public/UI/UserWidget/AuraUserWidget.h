// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI|Controller")
	TObjectPtr<UObject> WidgetController;
	
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
