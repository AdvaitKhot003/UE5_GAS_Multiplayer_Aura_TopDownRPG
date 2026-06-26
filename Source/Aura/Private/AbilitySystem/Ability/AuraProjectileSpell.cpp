// No Copyright.

#include "AbilitySystem/Ability/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor || !AvatarActor->HasAuthority()) return;
	
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor);
	if (!CombatInterface) return;
	
	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
		
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform,
		AvatarActor, Cast<APawn>(AvatarActor), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
	if (!Projectile) return;
	Projectile->FinishSpawning(SpawnTransform);
}
