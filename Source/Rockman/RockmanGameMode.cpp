// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RockmanGameMode.h"
#include "RockmanCharacter.h"

ARockmanGameMode::ARockmanGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ARockmanCharacter::StaticClass();	
}
