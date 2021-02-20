// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "ProjectSimulationCharacter.h"
#include "Components/TimelineComponent.h"
#include "AdvancedMovementComponent.generated.h"

/**
* Actor Component allowing advanced movement, such as
* Wall Running 
* Grappling
* Double Jump
**/
UCLASS()
class PROJECTSIMULATION_API UAdvancedMovementComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UAdvancedMovementComponent();
	/*********************** Double Jump ***********************/
	//Jump, with double jump logic
	UFUNCTION()
	void Jump();

	//Reset the jump counter
	UFUNCTION()
	void JumpReset();


	/*********************** Wall Run ***********************/
	//Set box for wall run logic
	UFUNCTION(BlueprintCallable)
	void SetWallRunBoxL(class UBoxComponent* inBox);
	UFUNCTION(BlueprintCallable)
	void SetWallRunBoxR(class UBoxComponent* inBox);
	UFUNCTION(BlueprintCallable)
	void SetGrappleCable(class UCableComponent* inCable);

	//The base wall run speed
	UPROPERTY(EditAnywhere, Category = WallRun)
	float WallRunSpeed = 2000.f;

	/*********************** Grapple ***********************/
	UFUNCTION()
	void OnGrapple();
	UFUNCTION()
	void OnGrappleRelease();
	UPROPERTY(EditAnywhere, Category = Grapple)
	float GrappleSpeed = 2.5f;
	UPROPERTY(EditAnywhere, Category = Grapple)
	float GrappleDistance = 3000.f;
	UPROPERTY(EditAnywhere, Category = Grapple)
	float GrappleDelay = 1.f;

protected:
	/***********************Base Functions ***********************/
	virtual void BeginPlay();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/***********************Wall Running Functions ***********************/
	UFUNCTION()
	void OnWallRunBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnWallRunBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnWallRunBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void TickTimeline();
	/***********************Grapple Hook***********************/
	UFUNCTION()
	void GrappleReset();
private:

	TArray<class AGrappleable*> CurrentlyRenderedGrapplePoints;

	/***********************Double Jump***********************/
	int pDoCounter = 0;
	/*Jump up in air*/
	void DoJump();
	/*Jump and lunge based on camera direction*/
	void DoLunge(bool resetMomementom);

	/***********************Wallrunning***********************/
	bool isPlaying = false;
	FVector pPlayerDirection;
	bool pOnWall;
	float pWallRunSpeed;
	TArray<uint32_t> pRunWallStr;
	UPROPERTY(Category = "WallRun", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallRunBoxLComponent;
	UPROPERTY(Category = "WallRun", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallRunBoxRComponent;	
	/***********************Grapple Hook***********************/
	UPROPERTY(Category = "Grapple", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCableComponent* GrappleCableComponent;
	bool pCanGrapple = true;
	bool pGrappleOverloadCheck = true;
	FVector pHookLocation;
}; 
