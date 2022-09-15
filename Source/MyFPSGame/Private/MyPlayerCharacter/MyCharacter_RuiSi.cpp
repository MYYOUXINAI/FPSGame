// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter/MyCharacter_RuiSi.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyAttributeComponent.h"


AMyCharacter_RuiSi::AMyCharacter_RuiSi()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	PrimaryAttackSocketName = "Muzzle_01";
	PrimaryAttackDelay = 0.26f;
}

void AMyCharacter_RuiSi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter_RuiSi::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter_RuiSi::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter_RuiSi::Jump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter_RuiSi::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter_RuiSi::SprintEnd);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMyCharacter_RuiSi::PrimaryAttack);
}




void AMyCharacter_RuiSi::MoveForward(float Value)
{
	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0.f;
	CameraRotation.Roll = 0.f;

	this->AddMovementInput(CameraRotation.Vector(), Value);
}

void AMyCharacter_RuiSi::MoveRight(float Value)
{
	FRotator CameraRotation = GetControlRotation();
	CameraRotation.Pitch = 0.f;
	CameraRotation.Roll = 0.f;

	const FVector RightVector = FRotationMatrix(CameraRotation).GetScaledAxis(EAxis::Y);
	this->AddMovementInput(RightVector, Value);
}

void AMyCharacter_RuiSi::SprintStart()
{
	const float OldSpeed = GetCharacterMovement()->MaxWalkSpeed;
	const float NewSpeed = OldSpeed + AttributeComp->SprintDeltaSpeed;

	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMyCharacter_RuiSi::SprintEnd()
{
	const float OldSpeed = GetCharacterMovement()->MaxWalkSpeed;
	const float NewSpeed = OldSpeed - AttributeComp->SprintDeltaSpeed;

	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AMyCharacter_RuiSi::PrimaryAttack()
{
	if(ensure(PrimaryAttackAnimMontage))	PlayAnimMontage(PrimaryAttackAnimMontage);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMyCharacter_RuiSi::PrimaryAttackDelay_Elapsed, PrimaryAttackDelay);
}

void AMyCharacter_RuiSi::PrimaryAttackDelay_Elapsed()
{



	if(ensure(PrimaryAttackProjectileClass))
	{
		/*
		 *spawn projectile by bone rotator
		 *FRotator BoneRotator = GetMesh()->GetSocketRotation("gun_barrel");
		BoneRotator.Yaw += 90.f;
		FVector StartLocation = GetMesh()->GetSocketLocation(PrimaryAttackSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(PrimaryAttackProjectileClass, StartLocation, BoneRotator, SpawnParams);*/

		FVector StartLocation = GetMesh()->GetSocketLocation(PrimaryAttackSocketName);
		FRotator SpawnActorRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector QueryStartLocation = GetPawnViewLocation();
		FVector QueryEndLocation = QueryStartLocation + GetControlRotation().Vector() * 5000.f;

		FHitResult Hit;
		if(GetWorld()->SweepSingleByObjectType(Hit,QueryStartLocation,QueryEndLocation,FQuat::Identity,ObjectQueryParams,Shape,QueryParams))
		{
			QueryEndLocation = Hit.ImpactPoint;
		}

		SpawnActorRotator = FRotationMatrix::MakeFromX(QueryEndLocation-StartLocation).Rotator();
		
		GetWorld()->SpawnActor<AActor>(PrimaryAttackProjectileClass, StartLocation, SpawnActorRotator,SpawnParams);
	}
}

/*
 FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();

		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000);

		FHitResult Hit;
		// returns true if we got to a blocking hit
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Overwrite trace end with impact point in world
			TraceEnd = Hit.ImpactPoint;
		}

		// find new direction/rotation from Hand pointing to impact point in world.
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
 *
 */