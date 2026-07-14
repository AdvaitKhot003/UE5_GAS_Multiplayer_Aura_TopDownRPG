// No Copyright.

#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Aura/Aura.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector AAuraCharacterBase::GetCombatSocketLocation() const
{
	check(WeaponMesh);
	return WeaponMesh->GetSocketLocation(WeaponTipSocket);
}

void AAuraCharacterBase::UpdateWarpTarget(const FVector& TargetLocation) const
{
	return GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocation(FName("WarpTarget"), TargetLocation);
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation() const
{
	return HitReactMontage;
}

void AAuraCharacterBase::InitAbilityCharacterInfo()
{
	
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	if (!HasAuthority()) return;
	check(GameplayEffectClass);
	
	UAbilitySystemComponent* TargetAsc = GetAbilitySystemComponent();
	check(TargetAsc);
	
	FGameplayEffectContextHandle EffectContextHandle = TargetAsc->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetAsc->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);
	
	if (!EffectSpecHandle.IsValid()) return;
	
	TargetAsc->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAsc);
}

void AAuraCharacterBase::InitDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes);
	ApplyEffectToSelf(DefaultSecondaryAttributes);
	ApplyEffectToSelf(DefaultVitalAttributes);
}

void AAuraCharacterBase::GiveCharacterStartUpAbilities()
{
	if (!HasAuthority()) return;
	
	UAuraAbilitySystemComponent* AuraAsc = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	AuraAsc->GiveCharacterStartUpAbilities(StartUpGameplayAbilities);
}
