// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
class IEnemyInterface;
struct FInputActionValue;
class UAuraInputConfig;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAuraInputConfig> AuraInputConfig;
	
	void Move(const FInputActionValue& InputActionValue);
	void AbilityInputPressed(FGameplayTag InInputTag);
	void AbilityInputHeld(FGameplayTag InInputTag);
	void AbilityInputReleased(FGameplayTag InInputTag);
	
	void TraceUnderCursor();
	void AutoRun();
	
	FHitResult CursorHitResult;
	
	TScriptInterface<IEnemyInterface> LastHitResultActor;
	TScriptInterface<IEnemyInterface> ThisHitResultActor;
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	
	FVector CachedDestination = FVector::ZeroVector;
	
	bool bIsAutoRunning = false;
	bool bIsTargeting = false;
	
	float FollowTime = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float ShortPressThreshold = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AutoRunAcceptanceRadius = 50.f;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<USplineComponent> Spline;
};
