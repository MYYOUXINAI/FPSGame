// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTurrets/MyTurretBase.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "MyActionComponent.h"
#include "MyAttributeComponent.h"
#include "MyUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"


AMyTurretBase::AMyTurretBase()
{
	

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<UMyActionComponent>("ActionComp");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TargetActorName = "TargetActor";

	LookAtLocation = FVector(100, 0, 250);

	PrimaryActorTick.bCanEverTick = true;
}


void AMyTurretBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMyTurretBase::MyOnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyTurretBase::OnHealthChanged);
}

FVector AMyTurretBase::GetLookAtLocation() const
{
	return LookAtLocation;
}

void AMyTurretBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AActor* TargetActor = GetTargetActor();
	if(TargetActor)
	{
		/* Update LookAt Location */
		LookAtLocation = TargetActor->GetActorLocation();
	}
}


AActor* AMyTurretBase::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (ensure(AIC))
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorName));
	}

	return nullptr;
}


void AMyTurretBase::SetTargetActor(AActor* NewTargetActor) const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (ensure(AIC))
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorName, NewTargetActor);
	}
}


void AMyTurretBase::MyOnPawnSeen(APawn* Pawn)
{
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);

		DrawDebugString(this->GetWorld(), GetActorLocation(), TEXT("Turrets Has Seen Target Actor!!!"), nullptr, FColor::Red, 1.5f, false, 1.5f);
	}
}


void AMyTurretBase::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{

	if (Delta < 0.0f)
	{
		/* when the targetActor is nullptr, set the damage causer as the targetActor */
		if (InstigatorActor != this && InstigatorActor==nullptr)
		{
			SetTargetActor(InstigatorActor);
		}

		if (ActiveHealthBar == nullptr)
		{
			if (ensure(HealthBarWidgetClass))
			{
				ActiveHealthBar = CreateWidget<UMyUserWidget>(GetWorld(), HealthBarWidgetClass);
				if (ActiveHealthBar)
				{
					ActiveHealthBar->AttachedActor = this;
					ActiveHealthBar->AddToViewport();
				}
			}
		}

		/* fix it when implementation the hit flash effect */
		{

		}

		if (NewHealth <= 0.0f)
		{
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			/* add the die effect of turret there */
			{
				
			}

			SetLifeSpan(5.0f);
		}

	}
}



