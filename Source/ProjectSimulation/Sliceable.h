// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sliceable.generated.h"


UCLASS()
class PROJECTSIMULATION_API ASliceable : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UProceduralMeshComponent* pm;


public:	
	// Sets default values for this actor's properties
	ASliceable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called On Construction
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
