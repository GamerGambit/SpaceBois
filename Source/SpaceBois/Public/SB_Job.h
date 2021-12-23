// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SB_Job.generated.h"

// This class does not need to be modified.
UCLASS(Blueprintable, Abstract)
class USB_Job : public UObject
{
	GENERATED_BODY()

public:
	// @TODO make this FText and add support for localization
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Title;

	// Supervisors, who this person answers to directly
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<USB_Job>> Supervisors;


	// @TODO make this FText and add support for localization
	// Custom supervisor text. Takes priority over \Supervisors. Useful for jobs like Munitions Officer who reports to "Bridge Officer", but only those assigned to weapons.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString SupervisorsCustom;

	//Selection screen color
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (HideAlphaChannel))
	FLinearColor SelectionColor;

	// @TODO make this FText and add support for localization
	// Useful for servers which prefer to only have access given to the places a job absolutely needs (Larger server population)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> MinimumAccess;

	// @TODO make this FText and add support for localization
	// Useful for servers which either have fewer players, so each person needs to fill more than one role, or servers which like to give more access.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FString> ExtendedAccess;

	// Require this many hours of playtime to select this job.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0"))
	float MinimumPlayerAgeHours;

	//How many players can be this job
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1"))
	int TotalPositions;

	//How many players can spawn in as this job
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1"))
	int SpawnPositions;

	//How many players have this job
	UPROPERTY(BlueprintReadOnly)
	int CurrentPositions;

	//If this is true, a text is printed to the player when jobs are assigned, telling them to let admins know that they have to disconnect.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool RequireNotifyAdmin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class USB_Outfit> Outfit;

public:
	// @TODO make this FText and add support for localization
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure)
	TArray<FString> GetAccess();

	UFUNCTION(BlueprintImplementableEvent)
	void PostSpawn(class APawn* pawn);

	// @TODO make this FText and add support for localization
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetSupervisorText();
};
