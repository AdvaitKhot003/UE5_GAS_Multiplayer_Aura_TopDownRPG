// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstance.generated.h"

class UCharacterMovementComponent;
class AAuraCharacterBase;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<AAuraCharacterBase> AuraCharacterBase;
	
	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> AuraMovementComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|LocomotionData")
	float GroundSpeed = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation|LocomotionData")
	bool bHasAcceleration = false;
	
	float CachedGroundSpeed = 0.f;
	bool bCachedHasAcceleration = false;
};
