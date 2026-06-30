// No Copyright.

#include "Character/AuraEnemyCharacter.h"
#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Components/WidgetComponent.h"
#include "UI/UserWidget/AuraUserWidget.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
}

void AAuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityCharacterInfo();
	
	BindHealthCallbacksToDependencies();
	
	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBarWidgetComponent->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}
	
	BroadcastHealthInitialValues();
}

void AAuraEnemyCharacter::InitAbilityCharacterInfo()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent())->AbilityCharacterInfoSet();
	InitDefaultAttributes();
}

void AAuraEnemyCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAuraEnemyCharacter, EnemyLevel);
}

void AAuraEnemyCharacter::OnRep_EnemyLevel(int32 OldEnemyLevel)
{
	
}

void AAuraEnemyCharacter::BroadcastHealthInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(GetAttributeSet());
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}

void AAuraEnemyCharacter::BindHealthCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(GetAttributeSet());
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
}

int32 AAuraEnemyCharacter::GetCharacterLevel() const
{
	return EnemyLevel;
}

void AAuraEnemyCharacter::HighlightEnemy()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemyCharacter::UnHighlightEnemy()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
