#include "MyActions/MyAction_TurretProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UMyAction_TurretProjectileAttack::UMyAction_TurretProjectileAttack()
{
	HandSocketName = "Muzzle_01";

	AttackAnimDelay = 0.2f;
	AttackInterval = 1.0f;
}

void UMyAction_TurretProjectileAttack::SetTargetActor(AActor* _TargetActor)
{
	TargetActor = _TargetActor;
}

void UMyAction_TurretProjectileAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	ACharacter* Character = Cast<ACharacter>(InstigatorActor);
	if(ensure(Character))
	{
		if(Character->HasAuthority())
		{
			UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator);

			FTimerHandle TimerHandle_AttackDelay;
			FTimerDelegate AttackDelegate;
			AttackDelegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, AttackDelegate, AttackAnimDelay, false);

			FTimerHandle TimerHandle_AttackIntervalDelay;
			FTimerDelegate AttackInterval_Delegate;
			AttackInterval_Delegate.BindUFunction(this, "AttackInterval_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackIntervalDelay, AttackInterval_Delegate, AttackInterval, false);
		}
	}
}




void UMyAction_TurretProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorActor)
{
	ACharacter* OwningCharacter = InstigatorActor;
	if (ensure(OwningCharacter))
	{
		if (ensure(ProjectileClass))
		{
			FVector SocketLocation = OwningCharacter->GetMesh()->GetSocketLocation(HandSocketName);

			if (ensure(TargetActor))
			{
				FVector TargetActorLocation = TargetActor->GetActorLocation();

				FRotator SpawnActorRotator = FRotationMatrix::MakeFromX(TargetActorLocation - SocketLocation).Rotator();

				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				SpawnParams.Instigator = OwningCharacter;

				GetWorld()->SpawnActor<AActor>(ProjectileClass, SocketLocation, SpawnActorRotator, SpawnParams);
			}
		}
	}

}

void UMyAction_TurretProjectileAttack::AttackInterval_Elapsed(ACharacter* InstigatorActor)
{
	StopAction(InstigatorActor);
}