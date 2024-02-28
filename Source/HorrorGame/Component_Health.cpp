// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Health.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UComponent_Health::UComponent_Health()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComponent_Health::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_Health::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UComponent_Health::RemoveHealth(float Amount)
{
	CurrentHealth = UKismetMathLibrary::FClamp(CurrentHealth - Amount, MinHealth, MaxHealth);
}

void UComponent_Health::AddHealth(float Amount)
{
	CurrentHealth = UKismetMathLibrary::FClamp(CurrentHealth + Amount, MinHealth, MaxHealth);
}

