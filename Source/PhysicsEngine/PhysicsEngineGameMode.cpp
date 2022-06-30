// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicsEngineGameMode.h"
#include "PhysicsEngineHUD.h"
#include "PhysicsEngineCharacter.h"
#include "UObject/ConstructorHelpers.h"

APhysicsEngineGameMode::APhysicsEngineGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APhysicsEngineHUD::StaticClass();
}
