// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SB_GameState.generated.h"

namespace RoundState
{
	extern SPACEBOIS_API const FName PreRound;
	extern SPACEBOIS_API const FName InProgress;
	extern SPACEBOIS_API const FName PostRound;
}

/**
 * 
 */
UCLASS()
class SPACEBOIS_API ASB_GameState : public AGameStateBase
{
	GENERATED_BODY()

		ASB_GameState(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_RoundState)
	FName RoundState;

	UFUNCTION()
	virtual void OnRep_RoundState();

public:
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	UFUNCTION(BlueprintCallable)
	void SetRoundState(FName newRoundState);

	// Returns the current state of the round
	UFUNCTION(BlueprintPure)
	FName GetRoundState() const;

	// Returns whether the current round is in progress (e.g. neither pre or post round)
	UFUNCTION(BlueprintPure)
	bool IsRoundInProgress() const;
};
