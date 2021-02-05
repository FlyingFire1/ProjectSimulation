// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "AdvancedMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSIMULATION_API UAdvancedMovementComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UAdvancedMovementComponent();
	UPROPERTY(EditAnywhere, Category = WallRun)
	class UBoxComponent* WallRunBoxComponent;
	UFUNCTION()
	void Jump();
	UFUNCTION()
	void JumpReset();
private:
	int doCounter = 0;
	void DoJump();
};
