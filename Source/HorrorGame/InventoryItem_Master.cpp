// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem_Master.h"

// Sets default values
AInventoryItem_Master::AInventoryItem_Master()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventoryItem_Master::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInventoryItem_Master::UseItem_Implementation()
{
}

// Called every frame
void AInventoryItem_Master::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

