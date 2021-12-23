// Fill out your copyright notice in the Description page of Project Settings.


#include "SB_Outfit.h"

void USB_Outfit::Equip(APawn* pawn)
{
	K2_PreEquip(pawn);

	if (Uniform)
	{
		// TODO equip Uniform
	}

	if (Suit)
	{
		// TODO equip Suit
	}

	if (Back)
	{
		// TODO equip Back
	}

	if (Belt)
	{
		// TODO equip Belt
	}

	if (Gloves)
	{
		// TODO equip Gloves
	}

	if (Shoes)
	{
		// TODO equip Shoes
	}

	if (Head)
	{
		// TODO equip Head
	}

	if (Mask)
	{
		// TODO equip Mask
	}

	if (Neck)
	{
		// TODO equip Neck
	}

	if (Ears)
	{
		// TODO equip Ears
	}

	if (Glasses)
	{
		// TODO equip Glasses
	}

	if (ID)
	{
		// TODO spawn ID, equip it, update the label to reflect the character's name
	}

	if (SuitStorage)
	{
		// TODO equip Suit Storage
	}

	if (Accessory)
	{
		// TODO equip accessory if Uniform is valid, else warn and do nothing
	}

	if (LeftHand)
	{
		// TODO equip Left Hand
	}

	if (RightHand)
	{
		// TODO equip Right Hand
	}

	if (LeftPocket)
	{
		// TODO equip Left Pocket
	}

	if (RightPocket)
	{
		// TODO equip Right Pocket
	}

	if (BackpackContents.Num() > 0)
	{
		for (const auto& content : BackpackContents)
		{
			// TODO equip content
		}
	}

	if (!Head && ToggleHelmet /*&& pawn is wearing a hardsuit*/)
	{
		// TODO toggle helmet on the hardsuit
	}

	K2_PostEquip(pawn);

	// TODO apply fingerprints

	if (Internals)
	{
		// TODO equip Internals
	}

	if (Implants.Num() > 0)
	{
		for (const auto& implant : Implants)
		{
			// TODO equip implant
		}
	}
}
