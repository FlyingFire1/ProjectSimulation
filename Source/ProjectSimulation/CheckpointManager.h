// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CheckpointManager.generated.h"

UCLASS()
class PROJECTSIMULATION_API ACheckpointManager : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ACheckpointManager();

	/*Box for checking if player falls*/
	UPROPERTY(Category = "Registration", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* DeathBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoints")
	TArray<class ACheckpoint*> Checkpoints;

	UFUNCTION()
	void ReloadFromLatestCheckpoint(class ACharacter* player);

	void ClearCurrent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Played when the death box is overlapped*/
	UFUNCTION()
	void OnDeathBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
