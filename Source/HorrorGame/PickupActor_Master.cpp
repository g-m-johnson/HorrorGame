// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor_Master.h"

#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APickupActor_Master::APickupActor_Master()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultSceneRoot);

	PromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidget"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void APickupActor_Master::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor_Master::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector NewWorldLocation = StaticMesh->GetComponentLocation();
	NewWorldLocation.Z += WidgetDistanceAboveMesh;
	PromptWidget->SetWorldLocation(NewWorldLocation);

	if (bShouldUpdateActor)
	{

	}
}

void APickupActor_Master::UpdateWidget()
{
	FVector SMWorld = StaticMesh->GetComponentLocation();
	//FVector PlayerCamWorld = PlayerRef->GetComponents()
	//AActor::GetComponents()

}

