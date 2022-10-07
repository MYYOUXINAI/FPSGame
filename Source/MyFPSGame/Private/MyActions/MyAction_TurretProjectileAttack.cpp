#include "MyActions/MyAction_TurretProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyAnim/MyTurretsBaseAnimInstance.h"

UMyAction_TurretProjectileAttack::UMyAction_TurretProjectileAttack()
{
	HandSocketName = "Muzzle_01";

	AttackAnimDelay = 0.02f;
	AttackInterval = 0.8f;
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
			UMyTurretsBaseAnimInstance* AnimInstance = Cast<UMyTurretsBaseAnimInstance>(Character->GetMesh()->GetAnimInstance());

			if(ensure(AnimInstance))
			{
				AnimInstance->Fire(true);
			}

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

	UMyTurretsBaseAnimInstance* AnimInstance = Cast<UMyTurretsBaseAnimInstance>(OwningCharacter->GetMesh()->GetAnimInstance());

	if (ensure(AnimInstance))
	{
		AnimInstance->Fire(false);
	}

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