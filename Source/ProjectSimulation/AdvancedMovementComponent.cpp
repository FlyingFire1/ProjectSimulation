// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedMovementComponent.h"
#include "GameFramework/Character.h"

UAdvancedMovementComponent::UAdvancedMovementComponent() 
{

}

void UAdvancedMovementComponent::Jump()
{
	doCounter++;
	switch (doCounter)
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
	doCounter = 0;
}

void UAdvancedMovementComponent::DoJump()
{
	Cast<ACharacter>(GetOwner())->LaunchCharacter(FVector(0, 0, 420), false, true);
}