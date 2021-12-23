// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SB_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBOIS_API ASB_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	/** Spawn a SpectatorPawn to use as a spectator and initialize it. By default it is spawned at the PC's current location and rotation. */
	virtual ASpectatorPawn* SpawnSpectatorPawn();
};
