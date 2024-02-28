// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor_Master.h"

#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "FirstPersonCharacterBase.h"


// Sets default values
APickupActor_Master::APickupActor_Master()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultSceneRoot);

	PromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidget"));
	PromptWidget->SetupAttachment(DefaultSceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StaticMesh);
	Sphere->SetSphereRadius(500);
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);

	PromptWidget->SetRelativeLocation(FVector(0,0,WidgetDistanceAboveMesh));
}

// Called when the game starts or when spawned
void APickupActor_Master::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<AFirstPersonCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickupActor_Master::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &APickupActor_Master::OnSphereEndOverlap);	
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
		UpdateWidget();
	}
}

void APickupActor_Master::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PromptWidget->SetVisibility(true);
	bShouldUpdateActor = true;
}

void APickupActor_Master::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PromptWidget->SetVisibility(false);
	bShouldUpdateActor = false;
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void APickupActor_Master::UpdateWidget_Implementation()
{
	FVector SMWorld = StaticMesh->GetComponentLocation();
	FVector PlayerWorld = PlayerRef->CameraComponent->GetComponentLocation();

	FHitResult Hit;
	bool bHasHit = GetWorld()->LineTraceSingleByChannel(Hit, SMWorld, PlayerWorld, ECollisionChannel::ECC_Visibility);

	if (!bHasHit)
	{
		PromptWidget->SetVisibility(true);
		
		FRotator LARot = UKismetMathLibrary::FindLookAtRotation(PromptWidget->GetComponentLocation(), PlayerWorld);
		PromptWidget->SetWorldRotation(LARot);

		float Dist = UKismetMathLibrary::Vector_Distance(Hit.TraceStart, Hit.TraceEnd);

		// TOGGLE PROMPT
		// PromptWidget->GetUserWidgetObject()
		
		if (Dist <= PickUpDistance)
		{
			EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
		else
		{
			DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
	}
	else
	{
		PromptWidget->SetVisibility(false);
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
}

