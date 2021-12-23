// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_AIWheeledVehiclePawn.h"
#include "SpaceBois/public/SB_WheeledVehicleMovementComp4W.h"

ASB_AIWheeledVehiclePawn::ASB_AIWheeledVehiclePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USB_WheeledVehicleMovementComp4W>(AWheeledVehicle::VehicleMovementComponentName))
{
	// NOP
}
