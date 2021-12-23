// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_GameState.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

namespace RoundState
{
    const FName PreRound = FName(TEXT("PreRound"));
    const FName InProgress = FName(TEXT("InProgress"));
    const FName PostRound = FName(TEXT("PostRound"));
}

ASB_GameState::ASB_GameState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    RoundState = RoundState::PreRound;
}

void ASB_GameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASB_GameState, RoundState);
}

void ASB_GameState::SetRoundState(FName newRoundState)
{
    RoundState = newRoundState;
}

FName ASB_GameState::GetRoundState() const
{
    return RoundState;
}

bool ASB_GameState::IsRoundInProgress() const
{
    return RoundState == RoundState::InProgress;
}

void ASB_GameState::OnRep_RoundState()
{
    // NOP
}
