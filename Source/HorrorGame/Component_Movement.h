// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Movement.generated.h"

class ACharacter;

UCLASS( BlueprintType, Blueprintable)
class HORRORGAME_API UComponent_Movement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Movement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartSprint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SprintTimer();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopSprint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RegenerateStamina();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartCrouch();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndCrouch();

	UFUNCTION(BlueprintCallable)
	void Initialise(ACharacter* Character);

	UFUNCTION(BlueprintCallable)
	void SetPlayerMaxWalkSpeed(float Speed);

	UPROPERTY(BlueprintReadOnly, Category = "Default")
	ACharacter* PlayerRef;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float SprintSpeed = 800.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float WalkSpeed = 400.f;



	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float MaxStamina = 100.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float CrouchSpeed = 100.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float CrouchHalfHeight = 44.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	bool bIsCrouching = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float MinStamina = 0.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	float CurrentStamina = 100.f;
};
