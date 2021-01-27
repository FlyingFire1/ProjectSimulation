// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeCombat.h"


// Sets default values for this component's properties
UMeleeCombat::UMeleeCombat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//Box Component
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	//Damage Type
	dt = CreateDefaultSubobject<UDamageType_Melee>(TEXT("MeleeDMGType"));
}


void UMeleeCombat::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ovlAct.Add(OtherActor);
}

void UMeleeCombat::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ovlAct.Remove(OtherActor);
}

void UMeleeCombat::Attack()
{

	//For each actor, call receive damage.
	for(AActor* m : ovlAct)
		m->ReceiveAnyDamage(damageAmount, dt, GetOwner()->GetInstigatorController(), GetOwner());
}

void UMeleeCombat::SetBox(UBoxComponent* inBox)
{
	/*box->DestroyComponent();*/
	UBoxComponent& boxComp = *box;
	boxComp.DestroyComponent();
	box = inBox;
}

// Called when the game starts
void UMeleeCombat::BeginPlay()
{
	Super::BeginPlay();
	box->OnComponentBeginOverlap.AddDynamic(this, &UMeleeCombat::OnOverlapBegin);        // set up a notification for when this component overlaps something
}

// Called every frame
void UMeleeCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

