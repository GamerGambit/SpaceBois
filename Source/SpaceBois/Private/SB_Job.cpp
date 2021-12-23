// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_Job.h"

TArray<FString> USB_Job::GetAccess_Implementation()
{
	TArray<FString> ret = MinimumAccess;

	/*
	/// @TODO check config if jobs have minimal access. if true, return \MinimumAccess, 
	if (true)
	{
		ret.Append(ExtendedAccess);
	}
	*/

	return ret;
}

FString USB_Job::GetSupervisorText()
{
	if (SupervisorsCustom.IsEmpty())
	{
		TArray<FString> supervisorNames;
		for (auto supervisor : Supervisors)
		{
			// @TODO this should NOT be creating the jobs, instead it should use the JobManager or something.
			USB_Job* superJob = NewObject<USB_Job>(this, supervisor->StaticClass());
			supervisorNames.Add(superJob->Title);
		}

		return FString::Join(supervisorNames, TEXT(", "));
	}

	return SupervisorsCustom;
}
