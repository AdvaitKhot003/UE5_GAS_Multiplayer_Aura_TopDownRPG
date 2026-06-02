// No Copyright.

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTargetActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (!HasAuthority()) return;
	
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAsc) return;
	
	FGameplayEffectContextHandle EffectContextHandle = TargetAsc->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	check(GameplayEffectClass);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	
	if (!EffectSpecHandle.IsValid()) return;
	
	const FActiveGameplayEffectHandle ActiveEffectHandle =
		TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	if (!ActiveEffectHandle.IsValid()) return;
	
	const UGameplayEffect* GameplayEffect = EffectSpecHandle.Data.Get()->Def.Get();
	if (!GameplayEffect) return;
	
	if (GameplayEffect->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		if (InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetAsc);
		}
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTargetActor(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTargetActor(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTargetActor(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTargetActor(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTargetActor(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTargetActor(TargetActor, InfiniteGameplayEffectClass);
	}
	
	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveActiveEffectsFromTargetActor(TargetActor);
	}
}

void AAuraEffectActor::RemoveActiveEffectsFromTargetActor(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAsc) return;
		
	TArray<FActiveGameplayEffectHandle> ActiveHandlesToRemove;
		
	for (const auto& HandlePair : ActiveEffectHandles)
	{
		if (HandlePair.Value != TargetAsc) continue;
		TargetAsc->RemoveActiveGameplayEffect(HandlePair.Key, 1);
		ActiveHandlesToRemove.Add(HandlePair.Key);
	}
		
	for (const auto& Handle : ActiveHandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
	}
}
