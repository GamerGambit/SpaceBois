// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SB_Interactable.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class SPACEBOIS_API USB_Interactable : public UInterface
{
	GENERATED_BODY()
};

class ISB_Interactable
{
	GENERATED_BODY()

public:
	/**
	* @param activator The Actor wanting to interact with us (e.g. could be a player wanting to activate a button)
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* activator);
};
