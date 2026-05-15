// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	virtual void HighlightEnemy() override;
	virtual void UnHighlightEnemy() override;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsHighlighted = false;
};
