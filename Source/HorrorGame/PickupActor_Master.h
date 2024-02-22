// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InventoryItem_Master.h"

#include "PickupActor_Master.generated.h"

class USceneComponent;
class UWidgetComponent;
class UStaticMeshComponent;
class USphereComponent;
class InventoryItem_Master;

UCLASS()
class HORRORGAME_API APickupActor_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor_Master();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;

	UPROPERTY()
	UWidgetComponent* PromptWidget;

	UPROPERTY()
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	USphereComponent* Sphere;

protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (DisplayPriority = "1"))
	TSubclassOf<AInventoryItem_Master> Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (DisplayPriority = "1"))
	bool bShouldUpdateActor = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (DisplayPriority = "1"))
	TSubclassOf<ACharacter> PlayerRef;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (DisplayPriority = "1"))
	int32 Amount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (DisplayPriority = "1"))
	float PickUpDistance = 250.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (DisplayPriority = "1"))
	float WidgetDistanceAboveMesh = 50.f;

private:
	void UpdateWidget();

};
