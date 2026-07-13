// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAnimMontage;
// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType, MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetCharacterLevel() const;
	virtual FVector GetCombatSocketLocation() const;
	virtual void UpdateWarpTarget(const FVector& TargetLocation) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UAnimMontage* GetHitReactMontage() const;
};
