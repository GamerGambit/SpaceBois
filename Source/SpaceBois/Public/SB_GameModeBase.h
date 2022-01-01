// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SB_GameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class SPACEBOIS_API ASB_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ASB_GameModeBase(const FObjectInitializer& ObjectInitializer);

public:
	/* ROUND STATE CODE */

	// Puts the game in pre-round state
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartPreRound();

	// Puts the round in progress
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartRound();

	// Puts the game into post-round state
	UFUNCTION(BlueprintCallable, Category = "Game")
	void Endround();

	/* END ROUND STATE CODE*/

	// Round timer
	UPROPERTY()
	FTimerHandle RoundTimer;

	// Amount of seconds between gamemode start, and round start.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = ( ClampMin = "1" ) )
	float PreRoundTime = 10.0f;

	// Amount of seconds between round end and gamemode restart
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = ( ClampMin = "1" ) )
	float PostRoundTime = 10.0f;

protected:
	class USB_JobManager* JobManager;
	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "StartPreRound"))
	void K2_StartPreRound();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "StartRound"))
	void K2_StartRound();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "EndRound"))
	void K2_EndRound();

public:
	virtual void InitGameState() override;
	virtual bool AllowPausing(APlayerController* PC = nullptr) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE USB_JobManager* GetJobManager() { return JobManager; }
};
