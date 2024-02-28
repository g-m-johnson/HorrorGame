// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor_Master.h"
#include "ItemDataStruct.generated.h"


/** Inventory item data struct */
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:
	/** Name of item */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ItemName;

	/** 2D texture icon */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	/* Item Description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ItemDescription;

	/** Total amount that can be stacked */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxStackAmount = 0;

	/** Actor respresented by struct */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class APickupActor_Master> PickupActor;

	/** Can use it? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanBeUsed = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanBeExamined = true;

	/** Can drop it? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanBeDropped = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* ExaminationMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ExaminationMeshOffset = 20.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator ExaminationMeshRotation;
};