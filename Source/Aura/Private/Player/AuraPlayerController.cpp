// No Copyright.

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/AuraInputConfig.h"
#include "EnhancedInput/AuraInputComponent.h"
#include "AuraGameplayTags.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
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
	
	if (!IsLocalController()) return;
	TraceUnderCursor();
	AutoRun();
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (!AuraAbilitySystemComponent)
	{
		// const AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(PlayerState);
		// AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
		
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::TraceUnderCursor()
{
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

void AAuraPlayerController::AutoRun()
{
	if (!bIsAutoRunning) return;
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(
			ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		
		const FVector DirectionOnSpline = Spline->FindDirectionClosestToWorldLocation(
			LocationOnSpline, ESplineCoordinateSpace::World);
		
		ControlledPawn->AddMovementInput(DirectionOnSpline);
		
		if ((LocationOnSpline - CachedDestination).Length() <= AutoRunAcceptanceRadius)
		{
			bIsAutoRunning = false;
		}
	}
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	
	AuraInputComponent->BindNativeInputAction(AuraInputConfig, AuraGameplayTags::Input_Move, ETriggerEvent::Triggered,
		this, &AAuraPlayerController::Move);
	
	AuraInputComponent->BindAbilityInputAction(AuraInputConfig, this, &ThisClass::AbilityInputPressed,
		&ThisClass::AbilityInputHeld, &ThisClass::AbilityInputReleased);
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

void AAuraPlayerController::AbilityInputPressed(FGameplayTag InInputTag)
{
	if (!InInputTag.MatchesTagExact(AuraGameplayTags::Input_LMB)) return;
	
	bIsTargeting = ThisHitResultActor ? true : false;
	bIsAutoRunning = false;
}

void AAuraPlayerController::AbilityInputHeld(FGameplayTag InInputTag)
{
	if (!InInputTag.MatchesTagExact(AuraGameplayTags::Input_LMB))
	{
		if (!GetAuraAbilitySystemComponent()) return;
		GetAuraAbilitySystemComponent()->OnAbilityInputHeld(InInputTag);
		return;
	}
	
	if (bIsTargeting)
	{
		if (!GetAuraAbilitySystemComponent()) return;
		GetAuraAbilitySystemComponent()->OnAbilityInputHeld(InInputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHitResult.IsValidBlockingHit())
		{
			CachedDestination = CursorHitResult.ImpactPoint;
		}
		
		if (APawn* ControlledPawn = GetPawn<APawn>())
		{
			const FVector Direction = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(Direction);
		}
	}
}

void AAuraPlayerController::AbilityInputReleased(FGameplayTag InInputTag)
{
	if (!InInputTag.MatchesTagExact(AuraGameplayTags::Input_LMB))
	{
		if (!GetAuraAbilitySystemComponent()) return;
		GetAuraAbilitySystemComponent()->OnAbilityInputReleased(InInputTag);
		return;
	}
	if (bIsTargeting)
	{
		if (!GetAuraAbilitySystemComponent()) return;
		GetAuraAbilitySystemComponent()->OnAbilityInputReleased(InInputTag);
	}
	else
	{
		const APawn* ControlledPawn = GetPawn<APawn>();
		if (!ControlledPawn) return;

		const bool bShortPress = FollowTime <= ShortPressThreshold;
		FollowTime = 0.f;

		if (!bShortPress) return;

		UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(
			this, ControlledPawn->GetActorLocation(), CachedDestination);

		if (!NavigationPath || NavigationPath->PathPoints.Num() == 0) return;

		Spline->ClearSplinePoints();

		for (const FVector& PointLocation : NavigationPath->PathPoints)
		{
			Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
		}

		CachedDestination = NavigationPath->PathPoints.Last();
		bIsAutoRunning = true;
	}
}
