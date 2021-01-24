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
	//TArray<FVector> verts;
	//TArray<FVector> normals;
	//TArray<FVector2D> uvs;
	//TArray<uint32> temptris;
	//TArray<int32> tris;
	//TArray<FColor> clr;
	//TArray<FProcMeshTangent> tans;

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	//mesh->SetStaticMesh(MeshAsset.Object);


	////Generic Function name to save time :);
	//FStaticMeshLODResources& dataarray = MeshAsset.Object->RenderData->LODResources[0];

	////Get Vertex Data;
	//int32 a = dataarray.GetNumVertices();
	//for (int32 i = 0; i < a; i++)
	//{
	//	FVector b = dataarray.VertexBuffers.PositionVertexBuffer.VertexPosition(i);
	//	verts.Add(b);
	//	FVector c = dataarray.VertexBuffers.StaticMeshVertexBuffer.VertexTangentZ(i);
	//	normals.Add(c);
	//	FVector2D d = dataarray.VertexBuffers.StaticMeshVertexBuffer.GetVertexUV(i, 0);
	//	uvs.Add(d);
	//	FProcMeshTangent e(dataarray.VertexBuffers.StaticMeshVertexBuffer.VertexTangentX(i), false);
	//	tans.Add(e);
	//}

	////Get Vertex Colours;
	//for (uint32 i = 0; i < dataarray.VertexBuffers.ColorVertexBuffer.GetNumVertices(); i++)
	//{
	//	FColor f = dataarray.VertexBuffers.ColorVertexBuffer.VertexColor(i);
	//	clr.Add(f);
	//	dataarray.IndexBuffer.GetCopy(temptris);
	//}
	//
	////Get Tris in uint32 format;
	//for (uint32& m : temptris)
	//{
	//	int32 e = m;
	//	tris.Add(e);
	//}
	//
	//pm->CreateMeshSection(0, verts, tris, normals, uvs, clr, tans, true);
	/*pm->CreateMeshSection(0, verts , .,*/
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(mesh, 0, pm, true);
	
}

// Called when the game starts or when spawned
void ASliceable::BeginPlay()
{
}

// Called every frame
void ASliceable::Tick(float DeltaTime)
{
}

