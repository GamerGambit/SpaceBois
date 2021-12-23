// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_SpectatorPawn.h"

#include "Components/SphereComponent.h"

ASB_SpectatorPawn::ASB_SpectatorPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UStaticMeshComponent>(ASB_SpectatorPawn::MeshComponentName))
{
	bReplicates = true;
}

bool ASB_SpectatorPawn::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	return ViewTarget->IsA<ASB_SpectatorPawn>();
}
