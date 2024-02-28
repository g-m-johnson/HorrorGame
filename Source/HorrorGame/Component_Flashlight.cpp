// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Flashlight.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"

#include "FirstPersonCharacterBase.h"

// Sets default values for this component's properties
UComponent_Flashlight::UComponent_Flashlight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComponent_Flashlight::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<AFirstPersonCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}


// Called every frame
void UComponent_Flashlight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComponent_Flashlight::Initialise(AFirstPersonCharacterBase* PlayerCharacter)
{
	PlayerRef = PlayerCharacter;
	FlashlightLight = PlayerRef->Flashlight;
}

void UComponent_Flashlight::ToggleFlashlight()
{
	if (FlashlightLight->IsVisible())
	{
		FlashlightLight->SetVisibility(false);
		UKismetSystemLibrary::K2_ClearTimer(this, "DepleteBatteryLife");
	}
	else
	{
		if (CurrentBatteryLevel > MinBatteryLevel)
		{
			SetIntensity();
			FlashlightLight->SetVisibility(true);
			UKismetSystemLibrary::K2_SetTimer(this, "DepleteBatteryLife", DepletionSpeed, true);
		}
	}
}

void UComponent_Flashlight::DepleteBatteryLife()
{
	CurrentBatteryLevel = UKismetMathLibrary::FClamp(CurrentBatteryLevel - DepletionAmount, MinBatteryLevel, MaxBatteryLevel);
	SetIntensity();

	if (CurrentBatteryLevel <= MinBatteryLevel)
	{
		FlashlightLight->SetVisibility(false);
		UKismetSystemLibrary::K2_ClearTimer(this, "DepleteBatteryLife");
	}
}

void UComponent_Flashlight::AddBatteryLife(float Amount)
{
	CurrentBatteryLevel = UKismetMathLibrary::FClamp(CurrentBatteryLevel + Amount, MinBatteryLevel, MaxBatteryLevel);
	SetIntensity();
}

void UComponent_Flashlight::SetIntensity()
{
	float Value = UKismetMathLibrary::MapRangeClamped(CurrentBatteryLevel, MinBatteryLevel, MaxBatteryLevel * FadingOutFraction, 0.0f, 1.0f);
	FlashlightLight->SetIESBrightnessScale(Value);
}

