// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Ability System Interface - Start **/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/** Ability System Interface - End **/
	
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE int32 GetPlayerLevel() const { return PlayerLevel; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_PlayerLevel, BlueprintReadOnly, Category = "Combat")
	int32 PlayerLevel = 1;
	
	UFUNCTION() void OnRep_PlayerLevel(int32 OldPlayerLevel);
};
