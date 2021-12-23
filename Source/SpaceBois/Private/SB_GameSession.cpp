// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_GameSession.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

void ASB_GameSession::RegisterServer()
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub)
    {
        IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
        if (Sessions.IsValid())
        {
            //AMyGameMode* MyGM = Cast<AMyGameMode>(GetWorld()->GetAuthGameMode());
            //if (MyGM)
            {
                FOnlineSessionSettings HostSettings;
                HostSettings.Set(SETTING_GAMEMODE, FString(/**MyGM->GetName()*/"TEST"), EOnlineDataAdvertisementType::ViaOnlineService);
                HostSettings.Set(SETTING_MAPNAME, GetWorld()->GetMapName(), EOnlineDataAdvertisementType::ViaOnlineService);
                HostSettings.bUsesPresence = false;
                HostSettings.bIsLANMatch = false;
                HostSettings.bIsDedicated = true;
                HostSettings.bShouldAdvertise = true;
                HostSettings.bAllowJoinInProgress = /*MyGM->bAllowJoinInProgress*/true;
                HostSettings.NumPublicConnections = MaxPlayers;
                HostSettings.bUseLobbiesIfAvailable = false;
                Sessions->CreateSession(0, NAME_GameSession, HostSettings);
            }
        }
    }
}
