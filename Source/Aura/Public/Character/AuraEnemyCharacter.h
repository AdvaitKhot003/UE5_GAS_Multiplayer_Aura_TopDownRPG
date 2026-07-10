// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfoConfig.h"
#include "AuraEnemyCharacter.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemyCharacter();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Enemy Interface - Start **/
	virtual void HighlightEnemy() override;
	virtual void UnHighlightEnemy() override;
	/** Enemy Interface - End **/
	
	/** Combat Interface - Start **/
	virtual int32 GetCharacterLevel() const override;
	/** Combat Interface - End **/
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
protected:
	virtual void InitAbilityCharacterInfo() override;
	virtual void InitDefaultAttributes() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;
	
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_EnemyLevel, BlueprintReadOnly, Category = "Combat")
	int32 EnemyLevel = 1;
	
	UFUNCTION() void OnRep_EnemyLevel(int32 OldEnemyLevel);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent;
	
	void BroadcastHealthInitialValues();
	void BindHealthCallbacksToDependencies();
};
