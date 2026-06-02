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
	UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAsc) return;
	
	FGameplayEffectContextHandle EffectContext = TargetAsc->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	check(GameplayEffectClass);
	
	const FGameplayEffectSpecHandle EffectSpec = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContext);
	if (!EffectSpec.IsValid()) return;
	
	TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	
}
