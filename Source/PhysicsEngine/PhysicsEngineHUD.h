// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PhysicsEngineHUD.generated.h"

UCLASS()
class APhysicsEngineHUD : public AHUD
{
	GENERATED_BODY()

public:
	APhysicsEngineHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

