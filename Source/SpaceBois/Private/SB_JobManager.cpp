// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_JobManager.h"
 
#include "AssetRegistry/AssetRegistryModule.h"

#include "SB_Job.h"

USB_JobManager::USB_JobManager(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // NOP
}

void USB_JobManager::LoadJobFromUClass(UClass* uclass)
{
    /// @TODO possibly add a whitelist/blacklist for jobs. Maybe the gamemode can specify which jobs to load?
    if (!uclass->HasAnyClassFlags(CLASS_Abstract) && uclass->IsChildOf(USB_Job::StaticClass()))
    {
        USB_Job* job = NewObject<USB_Job>(this, uclass);
        Jobs.Add(job);
        FString title = job->Title;

        UE_LOG(LogTemp, Warning, TEXT("Loaded Job: %s"), *title);
    }
}


void USB_JobManager::LoadJobs()
{
    for (TObjectIterator<UClass> It; It; ++It)
    {
        LoadJobFromUClass(*It);
    }

    FAssetRegistryModule* AssetRegistryModule = &FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
    TArray<FAssetData> AssetData;
    FARFilter Filter;
    Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
    Filter.PackagePaths.Add("/Game/Blueprints/Jobs");
    AssetRegistryModule->Get().GetAssets(Filter, AssetData);

    for (TArray<FAssetData>::TConstIterator PkgIter = AssetData.CreateConstIterator(); PkgIter; ++PkgIter)
    {
        FAssetData Asset = *PkgIter;
        UBlueprint* BlueAsset = Cast<UBlueprint>(Asset.GetAsset());
        LoadJobFromUClass(BlueAsset->GeneratedClass);
    }
}
