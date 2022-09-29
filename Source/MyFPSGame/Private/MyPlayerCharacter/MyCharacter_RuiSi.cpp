// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter/MyCharacter_RuiSi.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyAttributeComponent.h"
#include "MyPlayerInterfaceComponent.h"
#include "MyShootHelpLightComponent.h"
#include "Particles/ParticleSystem.h"


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

	InterfaceComp = CreateDefaultSubobject<UMyPlayerInterfaceComponent>("InterfaceComp");

	ShootHelpLightComp = CreateDefaultSubobject<UMyShootHelpLightComponent>("ShootHelpLightComp");
	ShootHelpLightComp->IgnoreActors.Add(this);

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

void AMyCharacter_RuiSi::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyCharacter_RuiSi::OnHealthChange);
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

void AMyCharacter_RuiSi::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	Super::GetActorEyesViewPoint(OutLocation, OutRotation);
	OutLocation = CameraComp->GetComponentLocation();
	OutRotation = CameraComp->GetComponentRotation();
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
		FVector StartLocation = GetMesh()->GetSocketLocation(PrimaryAttackSocketName);
		FRotator SpawnActorRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(3.0f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector QueryStartLocation = GetPawnViewLocation();

		FVector QueryEndLocation = QueryStartLocation + GetControlRotation().Vector() * 5000.f;
		//FVector QueryEndLocation = CameraComp->GetComponentLocation() + CameraComp->GetComponentRotation().Vector() * 5000.f;

		FHitResult Hit;
		if(GetWorld()->SweepSingleByObjectType(Hit,QueryStartLocation,QueryEndLocation,FQuat::Identity,ObjectQueryParams,Shape,QueryParams))
		{
			QueryEndLocation = Hit.ImpactPoint;
		}

		SpawnActorRotator = FRotationMatrix::MakeFromX(QueryEndLocation-StartLocation).Rotator();
		
		GetWorld()->SpawnActor<AActor>(PrimaryAttackProjectileClass, StartLocation, SpawnActorRotator,SpawnParams);
	}
}

void AMyCharacter_RuiSi::OnHealthChange(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(Delta<0.0f)
	{
		/* fix it when add hit flash effect */
		{
			
		}


		if(NewHealth<=0.0f)
		{
			APlayerController* PC = Cast<APlayerController>(GetController());
			if(PC)
			{
				DisableInput(PC);
				SetLifeSpan(3.0f);
			}
		}
	}
}
