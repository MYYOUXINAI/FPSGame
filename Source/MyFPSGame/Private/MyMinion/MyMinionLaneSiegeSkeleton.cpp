#include "MyMinion/MyMinionLaneSiegeSkeleton.h"

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


AMyMinionLaneSiegeSkeleton::AMyMinionLaneSiegeSkeleton()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	ActionComponent = CreateDefaultSubobject<UMyActionComponent>("ActionComp");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	TargetActorName = "TargetActor";
}

void AMyMinionLaneSiegeSkeleton::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMyMinionLaneSiegeSkeleton::MyOnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyMinionLaneSiegeSkeleton::OnHealthChanged);
}

AActor* AMyMinionLaneSiegeSkeleton::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (ensure(AIC))
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorName));
	}

	return nullptr;
}

void AMyMinionLaneSiegeSkeleton::SetTargetActor(AActor* NewTargetActor) const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (ensure(AIC))
	{
		AIC->GetBlackboardComponent()->SetValueAsObject(TargetActorName, NewTargetActor);
	}
}

void AMyMinionLaneSiegeSkeleton::MyOnPawnSeen(APawn* Pawn)
{
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);

		DrawDebugString(this->GetWorld(), GetActorLocation(), TEXT("Has Seen Target Actor!!!"), nullptr, FColor::Red, 1.5f, false, 1.5f);
	}
}

void AMyMinionLaneSiegeSkeleton::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp,
	float NewHealth, float Delta)
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


