// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USpotLightComponent;

UCLASS(Blueprintable, BlueprintType)
class HORRORGAME_API AFirstPersonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetupCameraComponent();
	void SetupSpringArmComponent();
	void SetupSpotlightComponent();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USpotLightComponent* Flashlight;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShortenPlayerCapsule();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LengthenPlayerCapsule();
};
