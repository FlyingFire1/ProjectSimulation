// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "DamageType_Melee.h"
#include "ProceduralMeshComponent.h"
#include "MeleeCombat.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSIMULATION_API UMeleeCombat : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeCombat();
	UPROPERTY(EditAnywhere, Category = Damage)
	float damageAmount;
	UPROPERTY(EditAnywhere, Category = Slicing)
	class UMaterialInterface* sliceMat;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void Attack();
	UFUNCTION(BlueprintCallable)
	void SetBox(UBoxComponent* inBox);
	UFUNCTION(BlueprintCallable)
	void FadeObject(UPrimitiveComponent* comp);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(Category = Registration, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* box;
	TArray<AActor*> ovlAct; //TArray of all overlapping actors;
	TArray<UProceduralMeshComponent*> ovlPM;
	UDamageType* dt;	//Damage Type, later defined as melee;
};
