// No Copyright.

#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Aura/Aura.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::Destroyed()
{
	/* Stop the looping projectile sound before the actor is removed. */
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->Stop();
	}
	
	/*
	 * Multiplayer timing note:
	 *
	 * Clients can receive the replicated Destroy() before or after
	 * their local overlap event is processed.
	 *
	 * If the projectile is destroyed BEFORE the client processes its overlap,
	 * Destroyed() is responsible for spawning the impact FX.
	 *
	 * We set bIsHit immediately so that any overlap event already queued by
	 * the collision system will see the flag and exit without spawning the
	 * impact a second time.
	 */
	if (!bIsHit && !HasAuthority())
	{
		bIsHit = true;

		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				ImpactSound,
				GetActorLocation(),
				FRotator::ZeroRotator
			);
		}
		
		if (ImpactEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				ImpactEffect,
				GetActorLocation()
			);
		}
	}
	
	Super::Destroyed();
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraProjectile::OnSphereEndOverlap);
	SetLifeSpan(ProjectileLifeSpan);
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(),
			FRotator::ZeroRotator);
	}
	
	if (LoopingSound)
	{
		LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
	}
}

void AAuraProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	 * Only allow the first hit to be processed.
	 * Multiple overlap events (or Destroyed() + overlap) can occur on clients due to replication timing.
	 */
	if (bIsHit) return;
	
	/*
	 * Mark the projectile as handled BEFORE doing anything else.
     * This closes the race window where another callback could also try to process the same impact.
     */
	bIsHit = true;

	/* Ignore any overlap fired while the actor is already being destroyed. */
	if (IsActorBeingDestroyed()) return;

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ImpactSound,
			GetActorLocation(),
			FRotator::ZeroRotator
		);
	}
	
	if (ImpactEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			ImpactEffect,
			GetActorLocation()
		);
	}
	
	/*
     * Server and clients play impact cosmetic feedback.
     * Only the server applies gameplay effects and destroys the projectile.
     */
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			if (DamageEffectSpecHandle.IsValid())
				TargetAsc->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}

		/* Replicated Destroy() will remove the projectile on every client. */
		Destroy();
	}
}

void AAuraProjectile::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
