// No Copyright.

#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
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

void AAuraCharacterBase::GrantCharacterStartUpAbilities()
{
	if (!HasAuthority()) return;
	
	UAuraAbilitySystemComponent* AuraAsc = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	AuraAsc->GrantCharacterStartUpAbilities(StartUpGameplayAbilities);
}
