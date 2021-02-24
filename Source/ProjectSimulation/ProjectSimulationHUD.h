// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDWidget.h"
#include "ProjectSimulationHUD.generated.h"

UCLASS()
class AProjectSimulationHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectSimulationHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
	TSubclassOf<UUserWidget> HitComboWidgetClass;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	UHUDWidget* HitComboWidget;

};

