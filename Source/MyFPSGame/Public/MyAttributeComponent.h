// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPSGAME_API UMyAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float SprintDeltaSpeed;




public:
	UMyAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		static UMyAttributeComponent* GetAttributes(AActor* InstigatorActor);

		
};

