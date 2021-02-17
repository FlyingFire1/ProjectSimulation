// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeCombat.h"
#include "Sliceable.h"
#include "Engine.h"
#include "GameFramework/Actor.h" 
#include "KismetProceduralMeshLibrary.h"

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
	if (OverlappedComponent->IsA(UProceduralMeshComponent::StaticClass()))
		ovlPM.Add(Cast<UProceduralMeshComponent>(OverlappedComponent));
	if (OtherComp->IsA(UProceduralMeshComponent::StaticClass()))
		ovlPM.Add(Cast<UProceduralMeshComponent>(OtherComp));

}

void UMeleeCombat::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ovlAct.Remove(OtherActor);
	if (OverlappedComponent->IsA(UProceduralMeshComponent::StaticClass()))
		ovlPM.Remove(Cast<UProceduralMeshComponent>(OverlappedComponent));
	if (OtherComp->IsA(UProceduralMeshComponent::StaticClass()))
		ovlPM.Remove(Cast<UProceduralMeshComponent>(OtherComp));
}

void UMeleeCombat::Attack()
{
	TArray<AActor*> temp;
	
	//Transfer every unique actor into temp;
	for (AActor* m : ovlAct)
		temp.AddUnique(m);
	

	//For each actor in temp, call receive damage.
	for (AActor* m : temp)
		m->ReceiveAnyDamage(damageAmount, dt, GetOwner()->GetInstigatorController(), GetOwner());
	

	//For each proc mesh, split in half.
	for (UProceduralMeshComponent* m : ovlPM)
	{
		FVector raycastLoc = box->GetComponentLocation();
		raycastLoc.Y += (box->GetScaledBoxExtent().Y / 2);
		raycastLoc += box->GetComponentLocation() - box->GetRelativeLocation();

		FHitResult* hr = new FHitResult();
		if (GetWorld()->LineTraceSingleByChannel(*hr, GetOwner()->GetActorLocation(), m->GetComponentLocation(), ECC_Visibility))
		{
			//Line For Debugging
			//DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), m->GetComponentLocation(), FColor(255, 0, 0), false, 2.f);
			UProceduralMeshComponent* procMesh;
			UKismetProceduralMeshLibrary::SliceProceduralMesh(m, hr->ImpactPoint, FVector(2, 4, 3), true, procMesh, EProcMeshSliceCapOption::CreateNewSectionForCap, sliceMat);
			//Make new proc mesh have physics
			procMesh->SetSimulatePhysics(true);
			procMesh->AddImpulse(FVector(50, 50, 50), NAME_None, true);

			//Timers for destroying
			FTimerHandle uHandle;
			FTimerDelegate dlg;
			dlg.BindUFunction(this, FName("FadeObject"), procMesh);
			GetWorld()->GetTimerManager().SetTimer(uHandle, dlg, 2.f, false);
			FTimerHandle uHandle2;
			FTimerDelegate dlg2;
			dlg2.BindUFunction(this, FName("FadeObject"), m);
			GetWorld()->GetTimerManager().SetTimer(uHandle2, dlg2, 2.f, false);
			//bogged but you could make a function inside melee combat that deletes the proc mesh.
		}
	}
}

void UMeleeCombat::FadeObject(UPrimitiveComponent* comp)
{
	comp->DestroyComponent();
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

