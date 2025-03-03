// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectSimulationCharacter.h"
#include "ProjectSimulationProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "MeleeCombat.h"
#include "Components/BoxComponent.h"
#include "AdvancedMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "CableComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AProjectSimulationCharacter

AProjectSimulationCharacter::AProjectSimulationCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create Melee Box
	MeleeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeBox"));
	MeleeBox->SetupAttachment(FirstPersonCameraComponent);

	// Create Melee Combat Component
	MeleeCombat = CreateDefaultSubobject<UMeleeCombat>(TEXT("MeleeComponent"));
	MeleeCombat->damageAmount = 20.f;
	MeleeCombat->SetBox(MeleeBox);

	//Advanced Movement Setup //
	AdvancedMovement = CreateDefaultSubobject<UAdvancedMovementComponent>(TEXT("AdvancedMovement"));

	//Wall Run Boxes
	WallRunBoxL = CreateDefaultSubobject<UBoxComponent>(TEXT("WallRunBoxL"));
	WallRunBoxL->SetupAttachment(GetCapsuleComponent());
	WallRunBoxL->SetGenerateOverlapEvents(true);
	WallRunBoxL->SetCollisionProfileName("OverlapAll");
	AdvancedMovement->SetWallRunBoxL(WallRunBoxL);

	WallRunBoxR = CreateDefaultSubobject<UBoxComponent>(TEXT("WallRunBoxR"));
	WallRunBoxR->SetupAttachment(GetCapsuleComponent());
	WallRunBoxR->SetGenerateOverlapEvents(true);
	WallRunBoxR->SetCollisionProfileName("OverlapAll");
	AdvancedMovement->SetWallRunBoxR(WallRunBoxR);

	//Grapple Cable
	GrappleCable = CreateDefaultSubobject<UCableComponent>(TEXT("Grapple Cable"));
	AdvancedMovement->SetGrappleCable(GrappleCable);

	// Timeline Setup //
	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/FirstPersonCPP/Blueprints/LinCurve.LinCurve'"));
	if (Curve.Object) {
		fCurve = Curve.Object;
	}

	ScoreTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineScore"));
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });
}

void AProjectSimulationCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.

	////Code for timer
	//FTimerDelegate TimerDel;
	//FTimerHandle TimerHandle;

	//TimerDel.BindUFunction(this, FName("PlayPainVoiceline"));

	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 4.f, true);



	//if (WidgetHUDClass)
	//{

	//	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), WidgetHUDClass);
	//	/** Make sure widget was created */
	//	if (HUDWidget)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Some debug message!"));
	//		/** Add it to the viewport */
	//		HUDWidget->AddToViewport();
	//	}
	//}
		ScoreTimeline->AddInterpFloat(fCurve, InterpFunction, FName{ TEXT("Float") });
}


void AProjectSimulationCharacter::TimelineFloatReturn(float val)
{

	if (!this->IsPendingKillPending() )
	{
		float roll = pUseRoll ? FMath::Lerp(pOGCamera.Roll, pCamera.Roll, val) : Controller->GetControlRotation().Roll;
		float yaw = pUseYaw ? Controller->GetControlRotation().Yaw : Controller->GetControlRotation().Yaw;
		float pitch = pUsePitch ? FMath::Lerp(pOGCamera.Pitch, pCamera.Pitch, val) : Controller->GetControlRotation().Pitch;
		FRotator temp;
		temp.Roll = roll;
		temp.Yaw = yaw;
		temp.Pitch = pitch;
		Controller->ClientSetRotation(temp);
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void AProjectSimulationCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AProjectSimulationCharacter::OnJump).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AProjectSimulationCharacter::OnJumpRelease);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AProjectSimulationCharacter::OnFire);
	
	// Bind Grapple event
	PlayerInputComponent->BindAction("Grapple", IE_Pressed, this, &AProjectSimulationCharacter::OnGrapple);
	PlayerInputComponent->BindAction("Grapple", IE_Released, this, &AProjectSimulationCharacter::OnGrappleRelease);

	//Bind Crouch event
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AProjectSimulationCharacter::OnCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AProjectSimulationCharacter::OnCrouchRelease);

	//Bind Sprint event
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AProjectSimulationCharacter::OnSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AProjectSimulationCharacter::OnSprintRelease);

	//Bind Pause event
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AProjectSimulationCharacter::Pause).bExecuteWhenPaused = true;

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectSimulationCharacter::MoveForward).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectSimulationCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectSimulationCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectSimulationCharacter::LookUpAtRate);
}

void AProjectSimulationCharacter::Landed(const FHitResult& Hit)
{
	AdvancedMovement->JumpReset();
}

void AProjectSimulationCharacter::OnGrapple()
{
	AdvancedMovement->OnGrapple();
}

void AProjectSimulationCharacter::OnGrappleRelease()
{
	AdvancedMovement->OnGrappleRelease();
}


void AProjectSimulationCharacter::OnFire()
{
	if (canSwing)
	{
		swingCount++;
		if (swingCount >= SwingAnims.Num())
			swingCount = 0;

		int32 id = swingCount;

		if (SwingAnims.IsValidIndex(id))
			Mesh1P->GetAnimInstance()->Montage_Play(SwingAnims[id], 1.f);
		if (SwingingSounds.IsValidIndex(id))
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SwingingSounds[id], GetActorLocation());
		
		canSwing = false;

		FTimerDelegate TimerDel;
		FTimerHandle TimerHandle;

		TimerDel.BindUFunction(this, FName("SwingWait"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, SwingSpeed, false);
	}
}

void AProjectSimulationCharacter::OnJump()
{
	if (Cast<APlayerController>(GetController())->IsPaused())
	{
		OnMenuSelect.Broadcast();
	}
	else
		AdvancedMovement->Jump();
}

void AProjectSimulationCharacter::OnJumpRelease()
{
	StopJumping();
}

void AProjectSimulationCharacter::OnCrouch()
{
	AdvancedMovement->OnCrouch();
}

void AProjectSimulationCharacter::OnCrouchRelease()
{
	AdvancedMovement->OnCrouchRelease();
}

void AProjectSimulationCharacter::OnSprint()
{
	AdvancedMovement->OnSprint();
}

void AProjectSimulationCharacter::OnSprintRelease()
{
	AdvancedMovement->OnSprintRelease();
}

void AProjectSimulationCharacter::Pause()
{
	APlayerController* pc = Cast<APlayerController>(GetController());
	if (!(pc->IsPaused()))
	{
		pc->SetPause(true);
		if (PauseMenuWidget)
		{
			pPauseMenu = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidget);

			/** Make sure widget was created */
			if (PauseMenuWidget)
			{

				pc->bShowMouseCursor = true;
				/** Add it to the viewport */
				pPauseMenu->AddToViewport();
			}
		}
	}
	else
	{
		pc->SetPause(false);
		if (pPauseMenu != NULL)
		{
			pc->bShowMouseCursor = false;
			pPauseMenu->RemoveFromParent();
		}
	}

}

void AProjectSimulationCharacter::MoveForward(float Value)
{

	if (Value != 0.0f)
	{

		if (Cast<APlayerController>(GetController())->IsPaused())
		{
			OnMenuMove.Broadcast(Value < 0);
		}
		else
		{
			// add movement in that direction
			AddMovementInput(GetActorForwardVector(), Value);

			//Footstep sound logic
			if (!isPlayingFootstep)
			{
				PlayFootstep();
			}
		}
	}
}



void AProjectSimulationCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);

		if (!isPlayingFootstep)
		{
			PlayFootstep();
		}
	}
}

void AProjectSimulationCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjectSimulationCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



//////////////////////////////////////////////////////////////////////////
// Manipulation Functions

/*Useful function for timers*/
void AProjectSimulationCharacter::FootstepWait()
{
	isPlayingFootstep = false;
}

/*Useful function for timers*/
void AProjectSimulationCharacter::SwingWait()
{
	//Attack using melee component;
	MeleeCombat->Attack();
	canSwing = true;

}

void AProjectSimulationCharacter::TauntWait()
{
	isPlayingTaunt = false;
}


/*Allows rotation of camera*/
void AProjectSimulationCharacter::RotateCamera(FRotator rotation, bool useRoll, bool usePitch, bool useYaw)
{

	pOGCamera = GetFirstPersonCameraComponent()->GetComponentRotation();

	pCamera = rotation;
	pUseRoll = useRoll;
	pUsePitch = usePitch;
	pUseYaw = useYaw;
	ScoreTimeline->PlayFromStart();
}

void AProjectSimulationCharacter::TakeDamage(float amount)
{
	Health -= amount;
	PlayPainVoiceline();
	if (!(Health > 0))
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()));
	}
}

//////////////////////////////////////////////////////////////////////////
// Sound Functions

/*Plays a footstep sound*/
void AProjectSimulationCharacter::PlayFootstep()
{
	UCharacterMovementComponent* cm = GetCharacterMovement();
	if (!cm->IsFalling())
	{
		footstepCount++;
		if (footstepCount > FootStepSounds.Num())
			footstepCount = 0;


		int32 id = footstepCount;

		if (FootStepSounds.IsValidIndex(id) && RunStepSounds.IsValidIndex(id))
		{
			USoundBase* chosenRunSound = RunStepSounds[id];
			USoundBase* chosenWalkSound = FootStepSounds[id];

			if (chosenWalkSound != NULL && chosenRunSound != NULL)
			{
				isPlayingFootstep = true;

				if (AdvancedMovement->GetIsSprinting())
				{

					UGameplayStatics::PlaySoundAtLocation(this, chosenRunSound, GetActorLocation());
					FTimerDelegate TimerDel;
					FTimerHandle TimerHandle;
					TimerDel.BindUFunction(this, FName("FootstepWait"));
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, (chosenRunSound->Duration) / 2, false);
				}
				else
				{
					UGameplayStatics::PlaySoundAtLocation(this, chosenWalkSound, GetActorLocation());
					FTimerDelegate TimerDel;
					FTimerHandle TimerHandle;
					TimerDel.BindUFunction(this, FName("FootstepWait"));
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, (chosenWalkSound->Duration), false);
				}
			}
		}
	}
}

/*Plays a random taunt sound*/
void AProjectSimulationCharacter::PlayTauntVoiceline()
{
	int32 id = FMath::RandRange(0, (TauntSounds.Num()-1));
	if (TauntSounds.IsValidIndex(id))
	{
		if (!isPlayingTaunt)
		{
			isPlayingTaunt = true;
			USoundBase* chosenSound = TauntSounds[id];
			UGameplayStatics::PlaySound2D(this, chosenSound);
		}
	}
}


/*Plays a random pain sound*/
void AProjectSimulationCharacter::PlayPainVoiceline()
{
	int32 id = FMath::RandRange(0, (PainSounds.Num()-1));
	if (PainSounds.IsValidIndex(id))
	{
		USoundBase* chosenSound = PainSounds[id];
		UGameplayStatics::PlaySoundAtLocation(this, chosenSound, GetActorLocation());
	}
}

void AProjectSimulationCharacter::PlayVaultVoiceline()
{
	int32 id = FMath::RandRange(0, (JumpSounds.Num()-1));
	if (JumpSounds.IsValidIndex(id))
	{
		USoundBase* chosenSound = JumpSounds[id];
		UGameplayStatics::PlaySoundAtLocation(this, chosenSound, GetActorLocation());
	}
}

void AProjectSimulationCharacter::PlayJumpVoiceline()
{
	int32 id = FMath::RandRange(0, (VaultSounds.Num()-1));
	if (VaultSounds.IsValidIndex(id))
	{
		USoundBase* chosenSound = VaultSounds[id];
		UGameplayStatics::PlaySoundAtLocation(this, chosenSound, GetActorLocation());
	}
}
