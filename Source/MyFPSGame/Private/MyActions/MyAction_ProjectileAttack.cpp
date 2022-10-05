
#include "MyActions/MyAction_ProjectileAttack.h"

#include "GameFramework/Character.h"

UMyAction_ProjectileAttack::UMyAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;

	SweepRadius = 20.0f;
	SweepDistanceFallback = 5000.f;

	AttackInterval = 1.0f;
}

void UMyAction_ProjectileAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	ACharacter* Character = Cast<ACharacter>(InstigatorActor);
	if(ensure(Character))
	{
		Character->PlayAnimMontage(AttackAnim);

		if(Character->HasAuthority())
		{
			FTimerHandle TimerHandle_AttackDelay;
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);

			FTimerHandle TimerHandle_AttackIntervalDelay;
			FTimerDelegate AttackInterval_Delegate;
			AttackInterval_Delegate.BindUFunction(this, "AttackInterval_Elapsed", Character);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackIntervalDelay, AttackInterval_Delegate, AttackInterval, false);

		}
	}
}


void UMyAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorActor)
{
	if (ensure(ProjectileClass))
	{
		FVector StartLocation = InstigatorActor->GetMesh()->GetSocketLocation(HandSocketName);
		FRotator SpawnActorRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SpawnParams.Instigator = InstigatorActor;

		FCollisionShape Shape;
		Shape.SetSphere(SweepRadius);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(InstigatorActor);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector QueryStartLocation = InstigatorActor->GetPawnViewLocation();

		FVector QueryEndLocation = QueryStartLocation +InstigatorActor-> GetControlRotation().Vector() * SweepDistanceFallback;

		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, QueryStartLocation, QueryEndLocation, FQuat::Identity, ObjectQueryParams, Shape, QueryParams))
		{
			QueryEndLocation = Hit.ImpactPoint;
		}

		SpawnActorRotator = FRotationMatrix::MakeFromX(QueryEndLocation - StartLocation).Rotator();

		GetWorld()->SpawnActor<AActor>(ProjectileClass, StartLocation, SpawnActorRotator, SpawnParams);
	}
}

void UMyAction_ProjectileAttack::AttackInterval_Elapsed(ACharacter* InstigatorActor)
{
	StopAction(InstigatorActor);
}


