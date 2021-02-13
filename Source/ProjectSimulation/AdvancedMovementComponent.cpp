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
	//Only jump twice, could be modified for more jumps later
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


//Set box for wall run logic
void UAdvancedMovementComponent::SetWallRunBox(UBoxComponent* inBox)
{
	//Destroy current box and replace it
	UBoxComponent& boxComp = *WallRunBoxComponent;
	boxComp.DestroyComponent();
	WallRunBoxComponent = inBox;
}

//Called upon the wall run box overlaps an object
void UAdvancedMovementComponent::OnWallRunBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor->ActorHasTag(TEXT("RunWall")) && Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement()->IsFalling()))
	{
		JumpReset(); //Reset Jump
		pRunWallStr.Add(OtherActor->GetUniqueID()); //Add to a temp storage, only way I could think of to keep wallrunning between comps

		//Initializing the beginning of the wall run
		pPlayerDirection = Cast<AProjectSimulationCharacter>(GetOwner())->GetFirstPersonCameraComponent()->GetForwardVector();
		pOnWall = true;
		pWallRunSpeed = WallRunSpeed;
		isPlaying = true;
	}
	else if (OtherComp->ComponentHasTag(TEXT("RunWall")) && Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement()->IsFalling())
	{
		JumpReset(); //Reset Jump
		pRunWallStr.Add(OtherComp->GetUniqueID()); //Add to a temp storage, only way I could think of to keep wallrunning between comps

		//Initializing the beginning of the wall run
		pPlayerDirection = Cast<AProjectSimulationCharacter>(GetOwner())->GetFirstPersonCameraComponent()->GetForwardVector();
		pOnWall = true;
		pWallRunSpeed = WallRunSpeed;
		isPlaying = true;
	}
}

//Called upon the wall run box ends overlap with an object
void UAdvancedMovementComponent::OnWallRunBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//here from testing, should be removed when u have time(u will probs forget)
	if (OtherActor->ActorHasTag(TEXT("RunWall")))
		pRunWallStr.Remove(OtherActor->GetUniqueID());
	else if (OtherComp->ComponentHasTag(TEXT("RunWall")))
		pRunWallStr.Remove(OtherComp->GetUniqueID());

	//If array(wall run objects) is empty, do this
	if (pRunWallStr.Num() == 0)
	{
		//Reset Gravity
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
	//Clamp wallrun speed
	if (pWallRunSpeed >= 100000)
		pWallRunSpeed = 100000;

	if (pOnWall)
	{
		//Constrain to the wall and force to run across it
		cm->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
		cm->GravityScale = 0.f;
		cm->AddForce(pPlayerDirection * pWallRunSpeed);
	}
}

void UAdvancedMovementComponent::BeginPlay()
{
	//Binding WallRunBox functions
	WallRunBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlap);
	WallRunBoxComponent->OnComponentEndOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlapEnd);

	//Setting Plane Constraints
	UCharacterMovementComponent* cm = Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement();
	cm->SetPlaneConstraintEnabled(true);
}

void UAdvancedMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Making my own timeline function(probs mega inefficio but whatevers)
	if (isPlaying)
		TickTimeline();
}

void UAdvancedMovementComponent::DoJump()
{
	if (pOnWall)
	{
		//Rotation of camera set to a fixed upwards angle
		FRotator rot = Cast<AProjectSimulationCharacter>(GetOwner())->GetFirstPersonCameraComponent()->GetComponentRotation();
		rot.Yaw = 60.f;

		//Get forward vector of rotation
		FVector temp = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
		temp *= (pWallRunSpeed / 150.f); 

		Cast<ACharacter>(GetOwner())->LaunchCharacter(temp, false, true);
	}
	else
		Cast<ACharacter>(GetOwner())->LaunchCharacter(FVector(0, 0, 420), false, true);
}

