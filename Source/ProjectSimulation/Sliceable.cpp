// Fill out your copyright notice in the Description page of Project Settings.


#include "Sliceable.h"
#include "Components/MeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "UObject/ObjectMacros.h"
#include "Misc/UObjectToken.h"
#include "Interfaces/Interface_CollisionDataProvider.h"
#include "Components/MeshComponent.h"
#include "MeshDescription.h"
#include "Rendering/MultiSizeIndexContainer.h"

#include "KismetProceduralMeshLibrary.h"



// Sets default values
ASliceable::ASliceable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	//Create Mesh
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	pm = CreateDefaultSubobject <UProceduralMeshComponent>(TEXT("ProceduralMesh"));

	RootComponent->SetRelativeLocation(FVector(0,0,0));
	mesh->SetupAttachment(RootComponent);
	mesh->SetVisibility(false);
	pm->SetupAttachment(RootComponent);
	pm->BodyInstance.SetCollisionProfileName("BlockAll");
	pm->SetSimulatePhysics(true);
	pm->bUseComplexAsSimpleCollision = false;
	mesh->BodyInstance.SetCollisionProfileName("NoCollision");
}

void ASliceable::OnConstruction(const FTransform& Transform)
{
	//Get Procedual mesh from Static Mesh
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(mesh, 0, pm, true);
	
}

// Called when the game starts or when spawned
void ASliceable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASliceable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

