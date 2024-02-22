// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SpotlightComponent.h"

// Sets default values
AFirstPersonCharacterBase::AFirstPersonCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(CameraComponent);
	SpotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	SpotlightComponent->SetupAttachment(SpringArmComponent);

	SetupCameraComponent();
	SetupSpringArmComponent();
	SetupSpotlightComponent();
}

// Called when the game starts or when spawned
void AFirstPersonCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPersonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFirstPersonCharacterBase::SetupCameraComponent()
{
	CameraComponent->AddRelativeLocation(FVector(0, 0, 60));
}

void AFirstPersonCharacterBase::SetupSpringArmComponent()
{
	SpringArmComponent->AddRelativeLocation(FVector(0, 0, -60));
	SpringArmComponent->TargetArmLength = 10.f;
	SpringArmComponent->SocketOffset = FVector(0,0,-30);
	SpringArmComponent->bEnableCameraRotationLag = true;
}

void AFirstPersonCharacterBase::SetupSpotlightComponent()
{
	SpotlightComponent->AddRelativeLocation(FVector(0, 0, 60));
	SpotlightComponent->AttenuationRadius = 1200;
}

