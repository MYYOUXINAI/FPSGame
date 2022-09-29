// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyAttributeComponent.generated.h"

class UMyAttributeComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UMyAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYFPSGAME_API UMyAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float SprintDeltaSpeed;

protected:
	//Attribute and data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float MaxMagicPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float CurrentMagicPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitReact")
		bool bIsHit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitReact")
		float HitAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitReact")
		float HitDelay;



public:
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnHealthChanged OnHealthChanged;



public:
	UMyAttributeComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		static UMyAttributeComponent* GetAttributes(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyHealthChange(AActor* InstigatorActor, float DamageValue);

	UFUNCTION(BlueprintCallable, Category = "MyHitReact")
		void MyRecoveryFromHit();

	UFUNCTION(BlueprintCallable, Category = "MyHitReact")
		void MyHitReact(const FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "CheckState")
		bool IsAlive()const;
};

