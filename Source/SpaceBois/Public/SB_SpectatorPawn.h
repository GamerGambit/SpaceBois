// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "SB_SpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBOIS_API ASB_SpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASB_SpectatorPawn(const FObjectInitializer& ObjectInitializer);

public:
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
};
