// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMinion/MyMinionLaneSuperCoreDawn.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "MyAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/PawnSensingComponent.h"



AMyMinionLaneSuperCoreDawn::AMyMinionLaneSuperCoreDawn()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TargetActorName = "TargetActor";
}

void AMyMinionLaneSuperCoreDawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMyMinionLaneSuperCoreDawn::MyOnPawnSeen);

}

void AMyMinionLaneSuperCoreDawn::SetTargetActor(AActor* NewTargetActor) const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if(ensure(AIC))
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorName, NewTargetActor);
	}
}

AActor* AMyMinionLaneSuperCoreDawn::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (ensure(AIC))
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorName));
	}

	return nullptr;
}

void AMyMinionLaneSuperCoreDawn::MyOnPawnSeen(APawn* Pawn)
{
	if(GetTargetActor()!=Pawn)
	{
		SetTargetActor(Pawn);

		DrawDebugString(this->GetWorld(), GetActorLocation(), TEXT("Has Seen Target Actor!!!"), nullptr, FColor::Red, 1.5f, false, 1.5f);
	}
}


