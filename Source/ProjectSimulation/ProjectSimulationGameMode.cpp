// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectSimulationGameMode.h"
#include "ProjectSimulationHUD.h"
#include "ProjectSimulationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectSimulationGameMode::AProjectSimulationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectSimulationHUD::StaticClass();
}
