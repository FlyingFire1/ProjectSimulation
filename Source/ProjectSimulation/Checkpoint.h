// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class PROJECTSIMULATION_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
	friend class ACheckpointManager;
public:	
	// Sets default values for this actor's properties
	ACheckpoint();
	UPROPERTY(Category = "Registration", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Checkbox;
	UPROPERTY(Category = "Spawn", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* SpawnLocation;
	UPROPERTY(Category = "Registration", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	ACheckpointManager* CMOwner;
	UFUNCTION(BlueprintCallable)
	void LoadCheckpoint(class ACharacter* player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnCheckBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	bool pActivated = false;
	bool pCurrent = false;
};
