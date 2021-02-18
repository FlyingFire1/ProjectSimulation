// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointManager.h"
#include "Components/BoxComponent.h"
#include "ProjectSimulationCharacter.h"
#include "Checkpoint.h"

// Sets default values
ACheckpointManager::ACheckpointManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeathBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Death Box"));
	RootComponent = DeathBox;

}

void ACheckpointManager::ReloadFromLatestCheckpoint(ACharacter* player)
{
	for (ACheckpoint* m : Checkpoints)
	{
		if (m->pCurrent)
		{
			m->LoadCheckpoint(player);
			break;
		}
	}
	
}

void ACheckpointManager::ClearCurrent()
{
	for (ACheckpoint* m : Checkpoints)
	{
		m->pCurrent = false;
	}
}

// Called when the game starts or when spawned
void ACheckpointManager::BeginPlay()
{
	Super::BeginPlay();
	DeathBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointManager::OnDeathBoxOverlap);
}

void ACheckpointManager::OnDeathBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AProjectSimulationCharacter::StaticClass()))
	{
		ReloadFromLatestCheckpoint(Cast<AProjectSimulationCharacter>(OtherActor));
	}
}

// Called every frame
void ACheckpointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
