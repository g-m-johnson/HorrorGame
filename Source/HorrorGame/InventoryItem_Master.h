// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataStruct.h"
#include "InventoryItem_Master.generated.h"

class AFirstPersonCharacterBase;

UCLASS()
class HORRORGAME_API AInventoryItem_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem_Master();

	FItemData GetItemData();

	bool GetUseItemSuccess();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (DisplayPriority = "1"))
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	AFirstPersonCharacterBase* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool UseItemSuccess;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
