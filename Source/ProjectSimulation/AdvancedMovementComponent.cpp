// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"
#include "Components/BoxComponent.h"
#include "ProjectSimulationCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAdvancedMovementComponent::UAdvancedMovementComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
	WallRunBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallRunBox"));
	
}

void UAdvancedMovementComponent::Jump()
{
	pDoCounter++;
	switch (pDoCounter)
	{
	case(1):
		DoJump();
		break;
	case(2):
		DoJump();
		break;
	default:
		break;
	}
}

void UAdvancedMovementComponent::JumpReset()
{
	pDoCounter = 0;
}

void UAdvancedMovementComponent::SetWallRunBox(UBoxComponent* inBox)
{
	UBoxComponent& boxComp = *WallRunBoxComponent;
	boxComp.DestroyComponent();
	WallRunBoxComponent = inBox;
}

void UAdvancedMovementComponent::OnWallRunBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("RunWall")) && Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement()->IsFalling())
	{
		pRunWallStrA.Add(OtherComp->GetUniqueID());
		tickUp++;
		pPlayerDirection = Cast<AProjectSimulationCharacter>(GetOwner())->GetFirstPersonCameraComponent()->GetForwardVector();
		pOnWall = true;
		pWallRunSpeed = WallRunSpeed;
		isPlaying = true;
	}
	else if (OtherComp->ComponentHasTag(TEXT("RunWall")) && Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement()->IsFalling())
	{
		pRunWallStrA.Add(OtherComp->GetUniqueID());
		tickUp++;
		pPlayerDirection = Cast<AProjectSimulationCharacter>(GetOwner())->GetFirstPersonCameraComponent()->GetForwardVector();
		pOnWall = true;
		pWallRunSpeed = WallRunSpeed;
		isPlaying = true;
	}
}

void UAdvancedMovementComponent::OnWallRunBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("RunWall")))
		pRunWallStrA.Remove(OtherActor->GetUniqueID());
	else if (OtherComp->ComponentHasTag(TEXT("RunWall")))
		pRunWallStrA.Remove(OtherComp->GetUniqueID());

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), pRunWallStrA.Num()));
	if ((pRunWallStrA.Num() + pRunWallStrC.Num()) == 0)
	{
		isPlaying = false;
		UCharacterMovementComponent* cm = Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement();
		cm->GravityScale = 1.f;
		cm->SetPlaneConstraintNormal(FVector(0, 0, 0));
		pOnWall = false;
	}
}

void UAdvancedMovementComponent::TickTimeline()
{
	UCharacterMovementComponent* cm = Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement();
	pWallRunSpeed *= 1.05;
	if (pWallRunSpeed >= 100000)
		pWallRunSpeed = 100000;
	if (pOnWall)
	{
		cm->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
		cm->GravityScale = 0.f;
		cm->AddForce(pPlayerDirection * pWallRunSpeed);
	}
}

void UAdvancedMovementComponent::BeginPlay()
{
	WallRunBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlap);
	WallRunBoxComponent->OnComponentEndOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlapEnd);
	UCharacterMovementComponent* cm = Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement();
	cm->SetPlaneConstraintEnabled(true);
}

void UAdvancedMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (isPlaying)
		TickTimeline();
}

void UAdvancedMovementComponent::DoJump()
{
	Cast<ACharacter>(GetOwner())->LaunchCharacter(FVector(0, 0, 420), false, true);
}

