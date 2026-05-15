// No Copyright.

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/AuraInputConfig.h"
#include "EnhancedInput/AuraInputComponent.h"
#include "AuraGameplayTags.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController()) return;

	checkf(AuraInputConfig, TEXT("AuraInputConfig is null! Assign it in the Blueprint defaults."));
	checkf(AuraInputConfig->InputMappingContext, TEXT("InputMappingContext is null on AuraInputConfig!"));

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	checkf(LocalPlayer, TEXT("LocalPlayer is null — is this controller locally owned?"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	checkf(Subsystem, TEXT("EnhancedInputLocalPlayerSubsystem not found for LocalPlayer!"));

	Subsystem->AddMappingContext(AuraInputConfig->InputMappingContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAuraInputComponent* AuraInputComponent = Cast<UAuraInputComponent>(InputComponent);
	checkf(AuraInputComponent,
		TEXT("AuraInputComponent is null! Set UAuraInputComponent as the Input Component class in Project Settings > Input."));
	
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
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = YawRotation.RotateVector(FVector::ForwardVector);
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = YawRotation.RotateVector(FVector::RightVector);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
