// Fill out your copyright notice in the Description page of Project Settings.


#include "Grappleable.h"

// Sets default values
AGrappleable::AGrappleable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrappleable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrappleable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

