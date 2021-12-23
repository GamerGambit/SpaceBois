// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SB_JobManager.generated.h"

class USB_Job;

/**
 * 
 */
UCLASS()
class SPACEBOIS_API USB_JobManager : public UObject
{
	GENERATED_BODY()

public:
	USB_JobManager(const FObjectInitializer& ObjectInitializer);

private:
	TArray<USB_Job*> Jobs;

	void LoadJobFromUClass(UClass* uclass);

public:
	void LoadJobs();
};
