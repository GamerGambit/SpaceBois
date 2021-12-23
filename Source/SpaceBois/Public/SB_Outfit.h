// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "SB_Item.h"

#include "SB_Outfit.generated.h"

class APawn;

USTRUCT(Blueprintable)
struct FBackpackContents
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = ( ClampMin = "1"))
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Item;
};

UCLASS(Blueprintable, Abstract)
class USB_Outfit : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Suit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ToggleHelmet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Back;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Belt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Gloves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Shoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Mask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Neck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Ears;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Glasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> LeftPocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> RightPocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> SuitStorage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Internals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBackpackContents> BackpackContents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<USB_Item>> Implants;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USB_Item> Accessory;

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = ( DisplayName = "PreEquip" ))
	void K2_PreEquip(APawn* pawn);

	UFUNCTION(BlueprintImplementableEvent, meta = ( DisplayName = "PostEquip" ))
	void K2_PostEquip(APawn* pawn);

public:
	UFUNCTION(BlueprintCallable)
	void Equip(APawn* pawn);

	UFUNCTION(BlueprintImplementableEvent)
	void PostSpawn(APawn* pawn);
};
