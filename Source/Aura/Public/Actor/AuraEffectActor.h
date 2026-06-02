// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

/**
 * 
 */
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTargetActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void RemoveActiveEffectsFromTargetActor(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
	/* Instant Gameplay Effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|InstantEffect")
	EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|InstantEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	/* Duration Gameplay Effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|DurationEffect")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|DurationEffect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	/* Infinite Gameplay Effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|InfiniteEffect")
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|InfiniteEffect")
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects|InfiniteEffect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
};
