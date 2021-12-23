// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "SB_GameSession.generated.h"

/**
 * 
 */
UCLASS()
class SPACEBOIS_API ASB_GameSession : public AGameSession
{
	GENERATED_BODY()

	virtual void RegisterServer() override;
};
