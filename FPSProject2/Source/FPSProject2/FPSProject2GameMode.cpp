// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProject2GameMode.h"
#include "FPSProject2HUD.h"
#include "FPSProject2Character.h"
#include "UObject/ConstructorHelpers.h"

AFPSProject2GameMode::AFPSProject2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSProject2HUD::StaticClass();
}
