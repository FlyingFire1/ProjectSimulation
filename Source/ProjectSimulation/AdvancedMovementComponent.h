// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "Components/TimelineComponent.h"
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
	float WallRunSpeed = 2000.f;
	UPROPERTY(Category = Melee, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallRunBoxComponent;
	float dt;

	//Jump, with double jump logic
	UFUNCTION()
	void Jump();

	//Reset the jump counter
	UFUNCTION()
	void JumpReset();

	//Set box for wall run logic
	UFUNCTION(BlueprintCallable)
	void SetWallRunBox(class UBoxComponent* inBox);
	
protected:
	UFUNCTION()
	void OnWallRunBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWallRunBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void TickTimeline();
	UFUNCTION()
	virtual void BeginPlay();
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	bool isPlaying = false;
	int pDoCounter = 0;
	void DoJump();
	FVector pPlayerDirection;
	bool pOnWall;
	float pWallRunSpeed;
	TArray<uint32_t> pRunWallStr;
};
