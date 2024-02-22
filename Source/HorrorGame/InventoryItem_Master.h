// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataStruct.h"
#include "InventoryItem_Master.generated.h"

UCLASS()
class HORRORGAME_API AInventoryItem_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem_Master();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (DisplayPriority = "1"))
	FItemData ItemData;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
