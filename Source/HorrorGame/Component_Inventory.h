// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Inventory.generated.h"

class AFirstPersonCharacterBase;
class UUserWidget;
class AInventoryItem_Master;
struct FInventoryItem;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORGAME_API UComponent_Inventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_Inventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	// FUNCTIONS

	bool AddItem(TSubclassOf<AInventoryItem_Master> Item, int Amount, int& ReturnRemainder);

	bool CheckForEmptySlot(int& ReturnIndex);

	TSubclassOf<AInventoryItem_Master> GetItemDataAtIndex(int Index, int& ReturnAmount);
	
	void UpdateInventorySlot(int Index);

	bool CheckForFreeSlot(TSubclassOf<AInventoryItem_Master> Item, int& ReturnIndex);

	void UseItem(int Index);

	void RemoveItem(int Index);

	void DropItem(int Index);

	void AddMoreSlots(int Amount);


	/* Reference to player character */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AFirstPersonCharacterBase* PlayerRef;

	/* Array of all items in inventory */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FInventoryItem> InventoryItems;

	/* Reference to inventory menu */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> InventoryMenuWidget;

	/* Reference to examination BP */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ExaminationActor;

	/* Refrerence to examination widget */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> ExaminationWidget;
};
