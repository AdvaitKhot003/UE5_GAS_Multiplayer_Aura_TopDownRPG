// No Copyright.

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/AuraInputConfig.h"
#include "EnhancedInput/AuraInputComponent.h"
#include "AuraGameplayTags.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	check(AuraInputConfig);
	check(AuraInputConfig->InputMappingContext);

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->AddMappingContext(AuraInputConfig->InputMappingContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	if (IsLocalController())
	{
		TraceUnderCursor();
	}
}

void AAuraPlayerController::TraceUnderCursor()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
	
	LastHitResultActor = ThisHitResultActor;
	ThisHitResultActor = nullptr;
	
	if (CursorHitResult.IsValidBlockingHit())
	{
		ThisHitResultActor = CursorHitResult.GetActor();
	}
	
	if (LastHitResultActor == ThisHitResultActor) return;
	if (LastHitResultActor) LastHitResultActor->UnHighlightEnemy();
	if (ThisHitResultActor) ThisHitResultActor->HighlightEnemy();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	
	AuraInputComponent->BindNativeInputAction(AuraInputConfig, AuraGameplayTags::Input_Move, ETriggerEvent::Triggered,
		this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);
	
	APawn* ControlledPawn = GetPawn<APawn>();
	if (!ControlledPawn) return;
	
	if (!FMath::IsNearlyZero(MovementVector.Y))
	{
		const FVector ForwardDirection = YawRotation.RotateVector(FVector::ForwardVector);
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (!FMath::IsNearlyZero(MovementVector.X))
	{
		const FVector RightDirection = YawRotation.RotateVector(FVector::RightVector);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
