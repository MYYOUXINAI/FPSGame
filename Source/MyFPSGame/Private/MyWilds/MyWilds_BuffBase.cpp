// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWilds/MyWilds_BuffBase.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "MyActionComponent.h"
#include "MyAttributeComponent.h"
#include "MyUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/PawnSensingComponent.h"


AMyWilds_BuffBase::AMyWilds_BuffBase()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	ActionComp = CreateDefaultSubobject<UMyActionComponent>("ActionComp");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TargetActorName = "TargetActor";
}

void AMyWilds_BuffBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyWilds_BuffBase::OnHealthChanged);

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMyWilds_BuffBase::MyOnPawnSeen);
}




AActor* AMyWilds_BuffBase::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if(ensure(AIC))
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorName));
	}

	return nullptr;
}

void AMyWilds_BuffBase::SetTargetActor(AActor* NewTargetActor) const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (ensure(AIC))
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorName, NewTargetActor);
	}
}


void AMyWilds_BuffBase::MyOnPawnSeen(APawn* Pawn)
{
	if(GetTargetActor()!=Pawn)
	{
		SetTargetActor(Pawn);

		DrawDebugString(this->GetWorld(), GetActorLocation(), TEXT("Wild Has Seen Target Actor!!!"), nullptr, FColor::Red, 1.0f, false, 1);
	}

}


void AMyWilds_BuffBase::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{

	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
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

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			SetLifeSpan(5.0f);
		}

	}
}




