// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/Character.h"
#include "ProjectSimulationCharacter.h"
#include "CheckpointManager.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Checkbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Checkbox"));
	SpawnLocation = CreateDefaultSubobject<UBillboardComponent>(TEXT("Spawn Location"));

	RootComponent = Checkbox;
	SpawnLocation->SetupAttachment(Checkbox);
}

void ACheckpoint::LoadCheckpoint(ACharacter* player)
{
	player->SetActorLocation(SpawnLocation->GetComponentLocation());
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	Checkbox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnCheckBoxOverlap);
	
}

void ACheckpoint::OnCheckBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AProjectSimulationCharacter::StaticClass()))
	{
		if (!pActivated)
		{
			pActivated = true;
			if(CMOwner->IsValidLowLevel())
				CMOwner->ClearCurrent();
			pCurrent = true;
		}
	}
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

