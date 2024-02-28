// Fill out your copyright notice in the Description page of Project Settings.


#include "Component_Inventory.h"

#include "InventoryItemStruct.h"
#include "InventoryItem_Master.h"
#include "FirstPersonCharacterBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"

#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UComponent_Inventory::UComponent_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComponent_Inventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComponent_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UComponent_Inventory::AddItem(TSubclassOf<AInventoryItem_Master> Item, int Amount, int& ReturnRemainder)
{
	TSubclassOf<AInventoryItem_Master> LocalItemClassRef = Item;
	int LocalAmount = Amount;
	int LocalMaxStackAmount = LocalItemClassRef.GetDefaultObject()->GetItemData().MaxStackAmount;

	if (LocalMaxStackAmount > 1)
	{
		int FreeSlotIndex;
		bool FreeSlotSuccess = CheckForFreeSlot(LocalItemClassRef, FreeSlotIndex);
		if (FreeSlotSuccess)
		{
			int LocalIndex = FreeSlotIndex;
			int Am;
			GetItemDataAtIndex(LocalIndex, Am);
			int Total = Am + LocalAmount;
			if (Total > LocalMaxStackAmount)
			{
				LocalAmount = Total - LocalMaxStackAmount;
				InventoryItems[LocalIndex].Item = LocalItemClassRef;
				InventoryItems[LocalIndex].Amount = LocalMaxStackAmount;

				UpdateInventorySlot(LocalIndex);

				int LocalRemainder;
				AddItem(LocalItemClassRef, LocalAmount, LocalRemainder);

				ReturnRemainder = LocalRemainder;
				return true;
			}
			else
			{
				InventoryItems[LocalIndex].Item = LocalItemClassRef;
				InventoryItems[LocalIndex].Amount = Total;

				UpdateInventorySlot(LocalIndex);

				ReturnRemainder = 0;
				return true;
			}
		}
		else
		{	
			int EmptySlotIndex;
			if (CheckForEmptySlot(EmptySlotIndex))
			{
				int LocalIndex = EmptySlotIndex;
				if (LocalAmount > LocalMaxStackAmount)
				{
					InventoryItems[LocalIndex].Item = LocalItemClassRef;
					InventoryItems[LocalIndex].Amount = LocalMaxStackAmount;

					UpdateInventorySlot(LocalIndex);

					int LocalRemainder;
					AddItem(LocalItemClassRef, LocalAmount - LocalMaxStackAmount, LocalRemainder);

					ReturnRemainder = LocalRemainder;
					return true;
				}
				else
				{
					InventoryItems[LocalIndex].Item = LocalItemClassRef;
					InventoryItems[LocalIndex].Amount = LocalAmount;

					UpdateInventorySlot(LocalIndex);

					ReturnRemainder = 0;
					return true;
				}
			}
			else
			{
				ReturnRemainder = LocalAmount;
				return false;
			}
		}
	}
	else
	{
		int EmptySlotIndex;
		if (CheckForEmptySlot(EmptySlotIndex))
		{
			int LocalIndex = EmptySlotIndex;
			
			FInventoryItem NewItem;
			NewItem.Item = LocalItemClassRef;
			NewItem.Amount = 1;

			InventoryItems[LocalIndex] = NewItem;

			UpdateInventorySlot(LocalIndex);

			if (LocalAmount - 1 > 0)
			{
				int ItemRemainder;
				AddItem(LocalItemClassRef, LocalAmount - 1, ItemRemainder);

				ReturnRemainder = ItemRemainder;
				return true;
			}
			else
			{
				ReturnRemainder = 0;
				return true;
			}
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), "No free slots");
			ReturnRemainder = LocalAmount;
			return false;
		}
	}
}

bool UComponent_Inventory::CheckForEmptySlot(int& ReturnIndex)
{
	bool Success = false;
	int Index = -1;
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (UKismetSystemLibrary::IsValidClass(InventoryItems[i].Item))
		{
			Success = false;
		}
		else
		{
			Success = true;
			Index = i;
			break;
		}
	}
	ReturnIndex = Index;
	return Success;
}

TSubclassOf<AInventoryItem_Master> UComponent_Inventory::GetItemDataAtIndex(int Index, int& ReturnAmount)
{
	FInventoryItem Item = InventoryItems[Index];
	ReturnAmount = Item.Amount;
	return *(Item.Item);
}

void UComponent_Inventory::UpdateInventorySlot(int Index)
{
}

bool UComponent_Inventory::CheckForFreeSlot(TSubclassOf<AInventoryItem_Master> Item, int& ReturnIndex)
{
	bool Success = false;
	int Index = -1;
	int MaxStackAmount = Cast<AInventoryItem_Master>(Item)->GetItemData().MaxStackAmount;

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i].Item == Item && InventoryItems[i].Amount < MaxStackAmount)
		{
			Success = true;
			Index = i;
			break;
		}
		else
		{
			Success = false;
		}
	}

	ReturnIndex = Index;
	return Success;
}

void UComponent_Inventory::UseItem(int Index)
{
	int LocalIndex = Index;

	int Amount;
	TSubclassOf<AInventoryItem_Master> Item = GetItemDataAtIndex(Index, Amount);

	if (Amount > 0)
	{
		AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), Item);
		if (IsValid(Actor))
		{
			AInventoryItem_Master* ItemRef = Cast<AInventoryItem_Master>(Actor);
			ItemRef->UseItem();
			if (ItemRef->GetUseItemSuccess())
			{
				// Remove item
				// Close drop down menu widget
			}
			else
			{
				UKismetSystemLibrary::PrintString(GetWorld(), "Use item not successful");
			}
		}
		else
		{
			AInventoryItem_Master* NewItem = GetWorld()->SpawnActor<AInventoryItem_Master>();
			NewItem->UseItem();
			if (NewItem->GetUseItemSuccess())
			{
				// Remove item
				// Close drop down widget
			}
			else
			{
				UKismetSystemLibrary::PrintString(GetWorld(), "Use item not successful");
			}
		}
	}
}

void UComponent_Inventory::RemoveItem(int Index)
{
	int LocalIndex = Index;
	int ReturnAmount;
	TSubclassOf<AInventoryItem_Master> ItemClassRef = GetItemDataAtIndex(LocalIndex, ReturnAmount);

	if (ReturnAmount > 1)
	{
		InventoryItems[LocalIndex].Item = ItemClassRef;
		InventoryItems[LocalIndex].Amount = ReturnAmount - 1;
	}
	else
	{
		TSubclassOf<AInventoryItem_Master> Empty;
		InventoryItems[LocalIndex].Item = Empty;
		InventoryItems[LocalIndex].Amount = 0;
	}

	UpdateInventorySlot(LocalIndex);
}

void UComponent_Inventory::DropItem(int Index)
{
	int LocalIndex = Index;
	int LocalAmount;
	TSubclassOf<AInventoryItem_Master> LocalItem = GetItemDataAtIndex(LocalIndex, LocalAmount);

	if (LocalAmount > 0)
	{
		for (int i = 0; i < LocalAmount - 1; i++)
		{
			RemoveItem(LocalIndex);
		}

		// Close drop down menu

		UCameraComponent* PlayerCam = PlayerRef->CameraComponent;
		FVector Start = PlayerCam->GetComponentLocation();
		FVector End = PlayerCam->GetForwardVector() * 200.f + Start;
		FHitResult HitResult;
		bool bHasHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

		AInventoryItem_Master* Item = Cast<AInventoryItem_Master>(LocalItem->GetDefaultObject());
		TSubclassOf<AActor> Actor = Item->GetItemData().PickupActor;
		FVector Loc = bHasHit ? HitResult.TraceStart : HitResult.TraceEnd;
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AActor>(Loc, FRotator(0,0,0), SpawnInfo);

		// cast to pickup actor
	}
}

void UComponent_Inventory::AddMoreSlots(int Amount)
{
	
}

