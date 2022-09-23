// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyShootHelpLightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPSGAME_API UMyShootHelpLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyShootHelpLightComponent();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Trace")
		FVector TargetLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trace")
		float TraceLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trace")
		TEnumAsByte<ETraceTypeQuery>TraceType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trace")
		float Radius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trace")
		TArray<AActor*>IgnoreActors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trace")
		bool bHasFindLocation;


	/* if the return value is (0,0,0),nothing has found! */
	UFUNCTION(BlueprintCallable, Category = "MyTrace")
		FVector GetTraceTargetLocation(AActor* InstigatorActor);
};
