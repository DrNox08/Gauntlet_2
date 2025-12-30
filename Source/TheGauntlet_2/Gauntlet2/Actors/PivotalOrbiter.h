// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gauntlet2/Interfaces/Activable.h"
#include "PivotalOrbiter.generated.h"

UCLASS()
class THEGAUNTLET_2_API APivotalOrbiter : public AActor, public IActivable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APivotalOrbiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> PivotRoot;

	// Platforms (Actors) to make orbit
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Orbit")
	TArray<TObjectPtr<AActor>> Platforms;

	//Orbit Radius
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Orbit", meta=(ClampMin="0.0"))
	float Radius = 300.f;

	// Angular Speed
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Orbit")
	float AngularSpeedDeg = 45.f;

	// State Variable
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Orbit")
	bool bActive = false;

	private:

	UPROPERTY(Transient)
	TArray<TObjectPtr<USceneComponent>> OrbitSlots;

	void RebuildSlotsAndAttachPlatforms();
	void ClearSlots();

	//IActivable
	virtual void BP_Activate_Implementation() override;
	virtual void BP_Deactivate_Implementation() override;

	virtual void NativeActivate() override { bActive = true;}
	virtual void NativeDeactivate() override{ bActive = false;}
};
