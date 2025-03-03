// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"
#include "Components/BoxComponent.h"
#include "ProjectSimulationCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "Grappleable.h"
#include "CableComponent.h"
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
		Cast<AProjectSimulationCharacter>(GetOwner())->PlayJumpVoiceline();
		DoJump();
		break;
	case(2):
		Cast<AProjectSimulationCharacter>(GetOwner())->PlayVaultVoiceline();
		isDoubleJumping = true;
		DoLunge(true);
		break;
	default:
		break;
	}
}

void UAdvancedMovementComponent::JumpReset()
{
	isDoubleJumping = false;
	pDoCounter = 0;
}

void UAdvancedMovementComponent::DoJump()
{
	if (pOnWall)
		DoLunge(false);
	else
	{
		if (pIsSlidingDown)
		{
			FRotator rot = Cast<AProjectSimulationCharacter>(GetOwner())->Controller->GetControlRotation();
			rot.Pitch = 60.f;
			rot.Roll = 0.f;

			//Get forward vector of rotation
			FVector temp = rot.Vector();
			temp *= 5000.f;
			temp.Z = 420.f;
			Cast<ACharacter>(GetOwner())->LaunchCharacter(temp, true, true);
			pIsSlidingDown = false;
		}
		else
			Cast<ACharacter>(GetOwner())->LaunchCharacter(FVector(0, 0, 420), false, true);
	}
}
void UAdvancedMovementComponent::DoLunge(bool resetMomementom)
{
	//Rotation of camera set to a fixed upwards angle
	FRotator rot = Cast<AProjectSimulationCharacter>(GetOwner())->Controller->GetControlRotation();
	rot.Pitch = 60.f;
	rot.Roll = 0.f;

	//Get forward vector of rotation
	FVector temp = rot.Vector();
	if (resetMomementom)
		temp *= Cast<ACharacter>(GetOwner())->GetCharacterMovement()->Velocity.GetAbsMax();
	else
		temp *= 1000.f;

	temp.Z = 700.f;


	Cast<ACharacter>(GetOwner())->LaunchCharacter(temp, resetMomementom, true);
}

//Grapple ***********************************************************************************
void UAdvancedMovementComponent::OnGrapple()
{
	if (pCanGrapple)
	{
		AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());

		//Find all grappleable actors
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGrappleable::StaticClass(), FoundActors);


		//if we actually found anything execute
		if (FoundActors.Num() > 0)
		{
			//temp vars
			bool found = false;
			TArray<AActor*> grappleObjects;

			for (AActor* m : FoundActors)
			{
				//Getting closest rendered grapple point
				if (CurrentlyRenderedGrapplePoints.Contains(m))
				{
					if (FVector::Dist(m->GetActorLocation(), GetOwner()->GetActorLocation()) < GrappleDistance)
					{
						grappleObjects.Add(m);
						found = true;
					}
				}
			}

			//if anything met previous criteria, execute
			if (found)
			{
				AActor* grappleTarget = nullptr;
				if (grappleObjects.Num() > 0)
				{

					FVector2D grappleTargetScreenLoc;
					for (AActor* m : grappleObjects)
					{
						//Getting if on screen
						const APlayerController* const PlayerController = Cast<const APlayerController>(Cast<AProjectSimulationCharacter>(GetOwner())->GetController());
						FVector2D ScreenLocation;

						PlayerController->ProjectWorldLocationToScreen(m->GetActorLocation(), ScreenLocation);

						int32 sizeX;
						int32 sizeY;

						PlayerController->GetViewportSize(sizeX, sizeY);

						if (FVector2D::Distance(FVector2D((sizeX / 2), (sizeY / 2)), ScreenLocation) < FVector2D::Distance(FVector2D((sizeX / 2), (sizeY / 2)), grappleTargetScreenLoc))
						{
							grappleTarget = m;
							grappleTargetScreenLoc = ScreenLocation;
						}
					}
				}

				if (grappleTarget->IsValidLowLevel())
				{
					pHookLocation = grappleTarget->GetActorLocation();

					GrappleCableComponent->SetWorldLocation(grappleTarget->GetActorLocation());
					GrappleCableComponent->SetVisibility(true);

					FVector hookMovement = (pHookLocation - player->GetFirstPersonCameraComponent()->GetComponentLocation()) * GrappleSpeed;
					player->LaunchCharacter(FVector(0, 0, 500), true, true);
					FTimerDelegate TimerDel;
					FTimerHandle TimerHandle;

					TimerDel.BindUFunction(player, FName("LaunchCharacter"), hookMovement, false, false);

					GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.1f, false, 0.f);
					pCanGrapple = false; //Disable Grapple
				}
			}

		}
		////Grapple from trace LEGACY

		////Check For Hit
		//FVector forVector = player->GetFirstPersonCameraComponent()->GetComponentLocation() + (player->Controller->GetControlRotation().Vector() * GrappleDistance);
		//FHitResult* hr = new FHitResult();
		//if (GetWorld()->LineTraceSingleByChannel(*hr, player->GetFirstPersonCameraComponent()->GetComponentLocation(), forVector, ECC_Visibility))
		//{
		//	//Verifying Actor(Stops Crash)
		//	if (hr->GetActor()->IsValidLowLevel())
		//	{
		//		//If object has the tag "CanGrapple" then grapple object
		//		if (hr->GetActor()->ActorHasTag(TEXT("CanGrapple")) || hr->GetComponent()->ComponentHasTag(TEXT("CanGrapple")))
		//		{
		//			pHookLocation = hr->Location;
		//			FVector hookMovement = (pHookLocation - player->GetFirstPersonCameraComponent()->GetComponentLocation()) * GrappleSpeed;
		//			player->LaunchCharacter(hookMovement, true, true);
		//			pCanGrapple = false; //Disable Grapple
		//		}
		//	}
		//}
	}
}

void UAdvancedMovementComponent::OnGrappleRelease()
{
	if (pGrappleOverloadCheck)
	{
		FTimerDelegate TimerDel;
		FTimerHandle TimerHandle;

		TimerDel.BindUFunction(this, FName("GrappleReset"));

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, GrappleDelay, false);
		TimerHandle.Invalidate();
		pGrappleOverloadCheck = false;

	}
}


void UAdvancedMovementComponent::GrappleReset()
{
	GrappleCableComponent->SetVisibility(false);
	pGrappleOverloadCheck = true;
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
	bool canGo = false;
	//here from testing, should be removed when u have time(u will probs forget)
	if (OtherActor->ActorHasTag(TEXT("RunWall")))
	{
		pRunWallStr.Remove(OtherActor->GetUniqueID());
		canGo = true;
	}
	else if (OtherComp->ComponentHasTag(TEXT("RunWall")))
	{
		pRunWallStr.Remove(OtherComp->GetUniqueID());
		canGo = true;
	}

	//If array(wall run objects) is empty, do this
	if ((pRunWallStr.Num() == 0) && canGo)
	{
		//Reset Gravity
		isPlaying = false;
		pOCM->GravityScale = 1.f;
		pOCM->SetPlaneConstraintNormal(FVector(0, 0, 0));
		pOnWall = false;

		AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());

		//rotating camera back to original position
		FRotator newRot = player->GetFirstPersonCameraComponent()->GetComponentRotation();
		newRot.Roll = 0;
		player->RotateCamera(newRot, true, false, false);
		if (pOCM->Velocity.Z < 0.f)
		{
			pOCM->Velocity.Z = 0.f;
		}
	}


}

void UAdvancedMovementComponent::OnWallRunBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherComp->ComponentHasTag(TEXT("RunWall")))
	{
	}
}

void UAdvancedMovementComponent::TickTimeline()
{
	pWallRunSpeed *= 1.05;
	//Clamp wallrun speed
	if (pWallRunSpeed >= 100000)
		pWallRunSpeed = 100000;

	if (pOnWall)
	{
		pWRTimer -= GetWorld()->GetDeltaSeconds();
		if (pWRTimer <= 0)
		{
			AProjectSimulationCharacter* player = Cast<AProjectSimulationCharacter>(GetOwner());
			
			
			pFootstepCount++;
			if (pFootstepCount > player->RunStepSounds.Num())
				pFootstepCount = 0;
			
			//Simple lerp
			pWRTimer = 0.05f + 0.265f * (1 - (player->GetVelocity().Size() / 2500.f));
			if (pWRTimer < 0.05f)
				pWRTimer = 0.05f;
			int32 id = pFootstepCount;

				if (player->RunStepSounds.IsValidIndex(id))
				{
					USoundBase* chosenRunSound = player->RunStepSounds[id];
					UGameplayStatics::PlaySoundAtLocation(this, chosenRunSound, player->GetActorLocation(), 0.25f, 0.5f);
				}
			
		}
	
		
		//Constrain to the wall and force to run across it
		pOCM->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));
		pOCM->GravityScale = 0.f;
		pOCM->AddForce(pPlayerDirection * pWallRunSpeed);
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

void UAdvancedMovementComponent::SetGrappleCable(UCableComponent* inCable)
{
	GrappleCableComponent = inCable;
	GrappleCableComponent->EndLocation = FVector(0, 0, 0);
	GrappleCableComponent->CableLength = 0;
	GrappleCableComponent->CableWidth = 8;
	GrappleCableComponent->NumSegments = 2;
	GrappleCableComponent->SetVisibility(false);
}


// Crouch Functions ***********************************************************************************


void UAdvancedMovementComponent::OnCrouch()
{

	if (pOCM->IsFalling())
	{
		pWaitCrouch = true; //Telling to wait until hit ground.
	}
	else
	{
		//Check if sprinting
		if ((GetOwner()->GetVelocity().GetAbs().X > pWalkSpeed) || (GetOwner()->GetVelocity().GetAbs().Y > pWalkSpeed) || (GetOwner()->GetVelocity().GetAbs().Z > pWalkSpeed))
		{
			PlaySlide();
		}
		else
		{
			Cast<AProjectSimulationCharacter>(GetOwner())->Crouch();
		}
	}
}

void UAdvancedMovementComponent::OnCrouchRelease()
{
	pWaitCrouch = false;
	Cast<AProjectSimulationCharacter>(GetOwner())->UnCrouch();
	pSlideTime = 0.f;
}

// Slide Functions **********************************************************************************
void UAdvancedMovementComponent::PlaySlide()
{
	pSlideDir = GetOwner()->GetVelocity();
	pSlideDir.Normalize(0.0001f);
	Cast<AProjectSimulationCharacter>(GetOwner())->Crouch();
	pSlideTime = 1;
}

// Sprint Functions *********************************************************************************

void UAdvancedMovementComponent::OnSprint()
{
	pIsSprinting = true;
	pOCM->MaxWalkSpeed = pRunSpeed;
}

void UAdvancedMovementComponent::OnSprintRelease()
{
	pIsSprinting = false;
	pOCM->MaxWalkSpeed = pWalkSpeed;
}
// Base Functions ***********************************************************************************
void UAdvancedMovementComponent::BeginPlay()
{
	//Binding WallRunBox functions
	//L
	WallRunBoxLComponent->OnComponentBeginOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlap);
	WallRunBoxLComponent->OnComponentEndOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlapEnd);

	//R
	WallRunBoxRComponent->OnComponentBeginOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlap);
	WallRunBoxRComponent->OnComponentEndOverlap.AddDynamic(this, &UAdvancedMovementComponent::OnWallRunBoxOverlapEnd);

	//Getting character movement as value, just for ease
	pOCM = Cast<AProjectSimulationCharacter>(GetOwner())->GetCharacterMovement();

	//Bind Walking/Running Speeds
	pWalkSpeed = pOCM->GetMaxSpeed();
	pRunSpeed = pWalkSpeed * 2;

	//Setting Plane Constraints
	pOCM->SetPlaneConstraintEnabled(true);
}

void UAdvancedMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Making my own timeline function(probs mega inefficio but whatevers)
	if (isPlaying)
		TickTimeline();

	//Thanks Rama :)
	UWorld*  World = GetOwner()->GetWorld();

	//Get all Grappleables in world
	for (TActorIterator<AGrappleable> Itr(World); Itr; ++Itr)
	{
		//Actor is rendered
		if (World->GetTimeSeconds() - Itr->GetLastRenderTime() <= 0.05f)
		{
			CurrentlyRenderedGrapplePoints.Add(*Itr);
		}
		//Actor is unrendered
		if (World->GetTimeSeconds() - Itr->GetLastRenderTime() > 0.05f)
		{
			CurrentlyRenderedGrapplePoints.Remove(*Itr);
		}

	}


	//Slide Logic ****************************************************

	//OnLanded is bugged and doesn't set isFalling to false the frame it is called, so I use this as a workaround
	if ((GetOwner()->GetVelocity().Z == 0.f) && pWaitCrouch)
	{
		pWaitCrouch = false;
		PlaySlide();
	}


	//Check if Sliding down hill
	bool slideDownCheck = (GetOwner()->GetActorLocation().Z < pPreviousFrameLoc.Z) && pOCM->IsCrouching() && !(pOCM->IsFalling());

	//Vector launch to apply
	FVector slideApply = ((pSlideDir * 2.0f) * (500.f * DeltaTime));


	if (!(pSlideTime <= 0.f))
	{
		if (!slideDownCheck && pOCM->IsCrouching())
		{
			Cast<AProjectSimulationCharacter>(GetOwner())->LaunchCharacter(slideApply * 2, false, false); //Launch Character in Slide Location
			pSlideTime -= DeltaTime; //Decrease Slide Time by Delta Time

			//Get Prev Frame Location for next Loop
			pPreviousFrameLoc = (GetOwner()->GetActorLocation());
		}
	}

	//Bogged way of checking if going down hill
	if (slideDownCheck)
	{
		GetOwner()->AddActorWorldOffset(slideApply * 3); //Add offset for smoother slide, no clue why
		pIsSlidingDown = true; //Used for BP and for jump
		pSlideTime += 1.f * DeltaTime; //Add slide time for longer slide when hitting the bottom of a slope.currently redundant 1.f but whatevs

		//Get Prev Frame Location for next Loop
		pPreviousFrameLoc = (GetOwner()->GetActorLocation());
	}
}
//***********************************************************************************
