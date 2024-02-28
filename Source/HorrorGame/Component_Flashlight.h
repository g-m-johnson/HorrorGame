// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Flashlight.generated.h"

class AFirstPersonCharacterBase;
class USpotLightComponent;

UCLASS(BlueprintType, Blueprintable, ClassGroup = "Custom", meta = (BlueprintSpawnableComponent))
class HORRORGAME_API UComponent_Flashlight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Flashlight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	AFirstPersonCharacterBase* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float MaxBatteryLevel = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float MinBatteryLevel = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float CurrentBatteryLevel = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float DepletionAmount = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float DepletionSpeed = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float FadingOutFraction = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USpotLightComponent* FlashlightLight;

	UFUNCTION(BlueprintCallable)
	void Initialise(AFirstPersonCharacterBase* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	void ToggleFlashlight();

	UFUNCTION(BlueprintCallable)
	void DepleteBatteryLife();

	UFUNCTION(BlueprintCallable)
	void AddBatteryLife(float Amount);

	void SetIntensity();
};
