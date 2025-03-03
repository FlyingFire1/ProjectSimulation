// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "ProjectSimulationCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuMoveDelegate, bool, isDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuSelectDelegate);

class UInputComponent;

UCLASS(config=Game)
class AProjectSimulationCharacter : public ACharacter
{
	GENERATED_BODY()
	
	friend class UAdvancedMovementComponent;  //Used for voicelines(dont want everything public

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/*Box for melee attacking*/
	UPROPERTY(Category = Melee, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* MeleeBox;

	/*Component that controls melee attacking*/
	UPROPERTY(Category = Melee, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMeleeCombat* MeleeCombat;

	/*Box for melee attacking*/
	UPROPERTY(Category = "AdvMovement", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallRunBoxL;

	/*Box for melee attacking*/
	UPROPERTY(Category = "AdvMovement", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WallRunBoxR;

	UPROPERTY(Category = "AdvMovement", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCableComponent* GrappleCable;

	UPROPERTY(Category = "AdvMovement", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAdvancedMovementComponent* AdvancedMovement;

	UPROPERTY(Category = "Pause", EditDefaultsOnly)
	TSubclassOf<class UUserWidget> PauseMenuWidget;
public:
	AProjectSimulationCharacter();

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FMenuMoveDelegate OnMenuMove;
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FMenuSelectDelegate OnMenuSelect;

	UFUNCTION()
	void RotateCamera(FRotator rotation, bool useRoll = true, bool usePitch = true, bool useYaw = true);

protected:
	virtual void BeginPlay();
public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AProjectSimulationProjectile> ProjectileClass;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<class UAnimMontage*> SwingAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 100.f;

	UFUNCTION()
	void PlayTauntVoiceline();

	UFUNCTION()
	void PlayPainVoiceline();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float amount);

	//Sounds 

	/** Sounds that are used for footsteps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> FootStepSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> RunStepSounds;

	/** Sounds that are used for taunts */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> TauntSounds;

	/** Sounds that are used for pain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> PainSounds;	
	
	/** Sounds that are used for Jumping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> JumpSounds;	
	
	/** Sounds that are used for Vaulting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> VaultSounds;	

	/** Sounds that are used for Swinging */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
	TArray<class USoundBase*> SwingingSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	float SwingSpeed = 0.15f;
protected:
	
	/** Fires a projectile. */
	void OnFire();

	// Called on Jumping
	void OnJump();

	// Called on release of Jumping
	void OnJumpRelease();

	// Called on Crouch
	void OnCrouch();

	// Called on release of Crouch
	void OnCrouchRelease();	
	
	// Called on Sprint
	void OnSprint();

	// Called on release of Sprint
	void OnSprintRelease();

	// Called when pausing
	void Pause();

	// Called upon hitting the ground, virtual function
	virtual void Landed(const FHitResult& Hit) override;

	//Called On grapple
	void OnGrapple();

	//Called on Grapple release
	void OnGrappleRelease();


	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);



	UPROPERTY()
	UTimelineComponent* ScoreTimeline;

	UPROPERTY()
	UCurveFloat* fCurve;

	FOnTimelineFloat InterpFunction{};

	float lerp = 0.f;

	UFUNCTION()
	void TimelineFloatReturn(float val);

private:
	/*******Sound*******/
	UFUNCTION()
	void FootstepWait();	
	
	UFUNCTION()
	void SwingWait();

	UFUNCTION()
	void TauntWait();

	UFUNCTION()
	void PlayFootstep();

	UFUNCTION()
	void PlayVaultVoiceline();	

	UFUNCTION()
	void PlayJumpVoiceline();


	bool isPlayingFootstep = false;
	bool canSwing = true;
	bool isPlayingTaunt = false;
	int32 footstepCount = 0;
	int32 swingCount = 0;
	/*******************/

	FRotator pOGCamera;
	FRotator pCamera;
	bool pUseRoll;
	bool pUsePitch;
	bool pUseYaw;

	//HUD/UI
	UUserWidget* pPauseMenu;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() { return FirstPersonCameraComponent; }

};

