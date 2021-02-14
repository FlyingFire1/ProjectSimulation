// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"
#include "Components/BoxComponent.h"
#include "ProjectSimulationCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

UAdvancedMovementComponent::UAdvancedMovementComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
	/*WallRunBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallRunBox"));*/
	
}

// Double Jump ***********************************************************************************
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
		Cast<AProjectSimulationCharacter>(GetOwner())->RotateCamera(FRotator(5.f, 0.f, 0.f), false, true, false);
		DoJump();
		break;
	default:
		break;
	}
}

void UAdvancedMovementComponent::JumpReset()
{
	Cast<AProjectSimulationCharacter>(GetOwner())->RotateCamera(FRotator(-2.5f, 0.f, 0.f), false, true, false);
	pDoCounter = 0;
}


void UAdvancedMovementComponent::DoJump()
{
	if (pOnWall)
	{
		//Rotation of camera set to a fixed upwards angle
		FRotator rot = Cast<AProjectSimulationCharacter>(GetOwner())->GetFirstPersonCameraComponent()->GetComponentRotation();
		rot.Pitch = 60.f;
		rot.Roll = 0.f;

		//Get forward vector of rotation
		FVector temp = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
		temp *= (pWallRunSpeed / 150.f);

		Cast<ACharacter>(GetOwner())->LaunchCharacter(temp, false, true);
	}
	else
		Cast<ACharacter>(GetOwner())->LaunchCharacter(FVector(0, 0, 420), false, true);
}

//Grapple ***********************************************************************************
void UAdvancedMovementComponent::OnGrapple()
{
	if (pCanGrapple)
	{
		AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());
		pCanGrapple = false; //Disable Grapple

		//Check For Hit
		FVector forVector = player->GetFirstPersonCameraComponent()->GetForwardVector() * GrappleDistance;
		FHitResult* hr = new FHitResult();
		if (GetWorld()->LineTraceSingleByChannel(*hr, player->GetFirstPersonCameraComponent()->GetComponentLocation(), forVector, ECC_Visibility))
		{
			DrawDebugLine(GetWorld(), player->GetFirstPersonCameraComponent()->GetComponentLocation(), forVector, FColor(255, 0, 0), false, 2.f);

			//If object has the tag "CanGrapple" then grapple object
			if (hr->GetActor()->ActorHasTag(TEXT("CanGrapple")) || hr->GetComponent()->ComponentHasTag(TEXT("CanGrapple")))
			{
				pHookLocation = hr->Location;
				FVector hookMovement = (pHookLocation - player->GetFirstPersonCameraComponent()->GetComponentLocation()) * GrappleSpeed;
				player->LaunchCharacter(hookMovement, true, true);
			}
		}
	}
}

void UAdvancedMovementComponent::OnGrappleRelease()
{
	pCanGrapple = true;
}

//Wall Running ***********************************************************************************

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



		AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());
		FRotator newRot = player->GetFirstPersonCameraComponent()->GetComponentRotation();



		//Check if we are running on the left or right, then apply camera roll
		if (OverlappedComponent->GetUniqueID() == WallRunBoxLComponent->GetUniqueID())
			newRot.Roll = 15.f;

		else
			newRot.Roll = -15.f;


		//Use Camera rotate Function
		player->RotateCamera(newRot, true, false, false);
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



		AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());
		FRotator newRot = player->GetFirstPersonCameraComponent()->GetComponentRotation();



		//Check if we are running on the left or right, then apply camera roll
		if (OverlappedComponent->GetUniqueID() == WallRunBoxLComponent->GetUniqueID())
			newRot.Roll = 15.f;

		else
			newRot.Roll = -15.f;


		//Use Camera rotate Function
		player->RotateCamera(newRot, true, false, false);
	}
}


//Called upon the wall run box ends overlap with an object
void UAdvancedMovementComponent::OnWallRunBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//here from testing, should be removed when u have time(u will probs forget)
	if (OtherActor->ActorHasTag(TEXT("RunWall")))
	{
		pRunWallStr.Remove(OtherActor->GetUniqueID());

	}
	else if (OtherComp->ComponentHasTag(TEXT("RunWall")))
	{
		pRunWallStr.Remove(OtherComp->GetUniqueID());
	}

	//If array(wall run objects) is empty, do this
	if (pRunWallStr.Num() == 0)
	{
		//Reset Gravity
		isPlaying = false;
		UCharacterMovementComponent* cm = Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement();
		cm->GravityScale = 1.f;
		cm->SetPlaneConstraintNormal(FVector(0, 0, 0));
		pOnWall = false;

		AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());

		//rotating camera back to original position
		FRotator newRot = player->GetFirstPersonCameraComponent()->GetComponentRotation();
		newRot.Roll = 0;
		player->RotateCamera(newRot, true, false, false);
	}

	
}

void UAdvancedMovementComponent::OnWallRunBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->ComponentHasTag(TEXT("RunWall")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, Hit.Location.ToText().ToString());
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

//Set box for wall run logic
void UAdvancedMovementComponent::SetWallRunBoxL(UBoxComponent* inBox)
{
	//Destroy current box and replace it
	WallRunBoxLComponent = inBox;
}

void UAdvancedMovementComponent::SetWallRunBoxR(UBoxComponent* inBox)
{
	//Destroy current box and replace it
	WallRunBoxRComponent = inBox;
}

// Base Functions ***********************************************************************************
void UAdvancedMovementComponent::BeginPlay()
{
	//Binding WallRunBox functions
	WallRunBoxLComponent->OnComponentBeginOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlap);
	WallRunBoxLComponent->OnComponentEndOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlapEnd);
	
	WallRunBoxRComponent->OnComponentBeginOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlap);
	WallRunBoxRComponent->OnComponentEndOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlapEnd);

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

//***********************************************************************************
