// No Copyright.

#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth)
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth)
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana)
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana)
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Cache Effect context Handle
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	AActor* Causer = Props.EffectContextHandle.GetEffectCauser();
	AActor* InstigatorActor = Props.EffectContextHandle.GetInstigator();

	/** SOURCE (Instigator + Effect Causer) **/
	
	// Source Ability System Component
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetInstigatorAbilitySystemComponent();

	// Source Avatar Actor
	if (Props.SourceAbilitySystemComponent)
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->GetAvatarActor();
	}
	else if (Causer)
	{
		Props.SourceAvatarActor = Causer;
	}
	else
	{
		Props.SourceAvatarActor = InstigatorActor;
	}
	
	// Source Controller
	if (const APawn* SourcePawn = Cast<APawn>(Props.SourceAvatarActor))
	{
		Props.SourceController = SourcePawn->GetController();
	}
	
	if (!Props.SourceController && InstigatorActor)
	{
		if (const APawn* InstigatorPawn = Cast<APawn>(InstigatorActor))
		{
			Props.SourceController = InstigatorPawn->GetController();
		}
	}

	// Source Character
	Props.SourceCharacter = Cast<ACharacter>(Props.SourceAvatarActor);

	if (!Props.SourceCharacter && Props.SourceController)
	{
		Props.SourceCharacter = Props.SourceController->GetCharacter();
	}

	/** TARGET (AttributeSet Owner) **/

	// Target Ability System Component
	Props.TargetAbilitySystemComponent = GetOwningAbilitySystemComponent();

	// Target Avatar Actor
	Props.TargetAvatarActor = Props.TargetAbilitySystemComponent ?
		Props.TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	// Target Controller
	if (const APawn* TargetPawn = Cast<APawn>(Props.TargetAvatarActor))
	{
		Props.TargetController = TargetPawn->GetController();
	}

	// Target Character
	Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

	if (!Props.TargetCharacter && Props.TargetController)
	{
		Props.TargetCharacter = Props.TargetController->GetCharacter();
	}
}
