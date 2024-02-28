// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Movement.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FirstPersonCharacterBase.h"

#include "Math/Vector.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UComponent_Movement::UComponent_Movement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComponent_Movement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_Movement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UComponent_Movement::StartSprint_Implementation()
{	
	if (bIsCrouching)
	{
		EndCrouch();
	}

	float vMagnitude = PlayerRef->GetVelocity().Size();

	if (CurrentStamina > MinStamina && vMagnitude > 10.f)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, "RegenerateStamina");
		SetPlayerMaxWalkSpeed(SprintSpeed);
		UKismetSystemLibrary::K2_SetTimer(this, "SprintTimer", 0.1, true);
	}
}

void UComponent_Movement::SprintTimer_Implementation()
{
	if (PlayerRef->GetVelocity().Size() > 10.f)
	{
		CurrentStamina = UKismetMathLibrary::FClamp(CurrentStamina - 1.f, MinStamina, MaxStamina);

		if (CurrentStamina <= MinStamina)
		{
			StopSprint();
		}
	}
	else
	{
		StopSprint();
	}
}

void UComponent_Movement::StopSprint_Implementation()
{
	if (!bIsCrouching)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, "SprintTimer");
		SetPlayerMaxWalkSpeed(WalkSpeed);

		// NEED DOING
/*
		FLatentActionInfo LatentAction;
		LatentAction.ExecutionFunction
		UKismetSystemLibrary::RetriggerableDelay(GetWorld(), 5.f, )*/
	}
}

void UComponent_Movement::RegenerateStamina_Implementation()
{
	CurrentStamina = UKismetMathLibrary::FClamp(CurrentStamina + 1.f, 0.0f, MaxStamina);
	if (CurrentStamina >= MaxStamina)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, "RegenerateStamina");
	}
}

void UComponent_Movement::StartCrouch_Implementation()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "SprintTimer");
	SetPlayerMaxWalkSpeed(CrouchSpeed);
	Cast<AFirstPersonCharacterBase>(PlayerRef)->ShortenPlayerCapsule();
	bIsCrouching = true;
}

void UComponent_Movement::EndCrouch_Implementation()
{
	SetPlayerMaxWalkSpeed(WalkSpeed);
	Cast<AFirstPersonCharacterBase>(PlayerRef)->LengthenPlayerCapsule();
	bIsCrouching = false;
}

void UComponent_Movement::Initialise(ACharacter* Character)
{
	PlayerRef = Character;
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void UComponent_Movement::SetPlayerMaxWalkSpeed(float Speed)
{
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = Speed;
}
