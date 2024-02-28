// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Health.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORGAME_API UComponent_Health : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Health();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MinHealth = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentHealth = 100.0f;


	UFUNCTION(BlueprintCallable)
	void RemoveHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void AddHealth(float Amount);
};
