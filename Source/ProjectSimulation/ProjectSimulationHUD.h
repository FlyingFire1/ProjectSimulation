// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectSimulationHUD.generated.h"

UCLASS()
class AProjectSimulationHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectSimulationHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

