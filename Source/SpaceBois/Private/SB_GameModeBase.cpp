// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_GameModeBase.h"
#include "SB_GameSession.h"
#include "SB_PlayerController.h"
#include "SB_SpectatorPawn.h"
#include "SB_GameState.h"
#include "SB_Character.h"
#include "SB_JobManager.h"

#include "GameFramework/PlayerState.h"
#include "GameFramework/DefaultPawn.h"

ASB_GameModeBase::ASB_GameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bStartPlayersAsSpectators = true;
	bUseSeamlessTravel = true;

	GameSessionClass = ASB_GameSession::StaticClass();
	PlayerControllerClass = ASB_PlayerController::StaticClass();
	SpectatorClass = ASB_SpectatorPawn::StaticClass();
	GameStateClass = ASB_GameState::StaticClass();
}

void ASB_GameModeBase::StartPreRound()
{
	GetGameState<ASB_GameState>()->SetRoundState(RoundState::PreRound);
	UE_LOG(LogTemp, Warning, TEXT("GM:StartPreRound, starting round in %f seconds"), PreRoundTime);
	GetWorld()->GetTimerManager().SetTimer(RoundTimer, this, &ASB_GameModeBase::StartRound, PreRoundTime, false);
	K2_StartPreRound();
}

void ASB_GameModeBase::StartRound()
{
	GetGameState<ASB_GameState>()->SetRoundState(RoundState::InProgress);
	UE_LOG(LogTemp, Warning, TEXT("GM:StartRound, round started"));
	GetWorld()->GetTimerManager().ClearTimer(RoundTimer);
	K2_StartRound();

	for (auto ps : GetGameState<ASB_GameState>()->PlayerArray)
	{
		auto pc = Cast<APlayerController>(ps->GetOwner());
		RestartPlayer(pc);
	}
}

void ASB_GameModeBase::Endround()
{
	GetGameState<ASB_GameState>()->SetRoundState(RoundState::PostRound);
	GetWorld()->GetTimerManager().SetTimer(RoundTimer, this, &ASB_GameModeBase::Reset, PostRoundTime, false);
	K2_EndRound();
}

void ASB_GameModeBase::InitGameState()
{
	Super::InitGameState();

	UE_LOG(LogTemp, Warning, TEXT("GM:InitGameState, loading jobs"));
	JobManager = NewObject<USB_JobManager>(this, USB_JobManager::StaticClass());
	JobManager->LoadJobs();

	UE_LOG(LogTemp, Warning, TEXT("GM:InitGameState, starting pre-round"));
	StartPreRound();
}

bool ASB_GameModeBase::AllowPausing(APlayerController* PC)
{
	// Dont allow pausing on dedicated.. maybe this is a mistake?
	// We can tie this in with the TODO below
	if (GetNetMode() == NM_DedicatedServer)
		return false;

	if (PC == nullptr)
		return false; // Not sure if this is a valid situation, but just making sure

	// TODO maybe add a list, or checkbox, to allow multiple players to pause
	return PC == GetWorld()->GetFirstPlayerController();
}

