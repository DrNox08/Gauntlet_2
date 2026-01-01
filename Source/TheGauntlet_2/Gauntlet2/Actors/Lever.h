// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gauntlet2/Interfaces/Activable.h"
#include "Gauntlet2/Interfaces/Interactable.h"
#include "Lever.generated.h"

UCLASS()
class THEGAUNTLET_2_API ALever : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALever();

	// Meshes

	UPROPERTY(Blueprintreadwrite, EditAnywhere, Category = "Components")
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(Blueprintreadwrite, EditAnywhere, Category = "Components")
	UStaticMeshComponent* LeverMesh;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Interaction", meta = (MustImplement = "Activable"))
	TObjectPtr<AActor> ActorToControl;

	IActivable* Activable = nullptr;

	//Animation
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	float AnimationDuration = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	float HoldDuration = 2.0f;

	//Materials
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Materials")
	UMaterialInstance* ActivatedMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Materials")
	UMaterialInstance* DeactivatedMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// State variables
	bool bIsInteracted = false;
	bool bIsReturning = false;

	FTimerHandle TimerHandle;
	FTimerHandle HoldTimerHandle;


	float ElapsedTime = 0.0f;

	FRotator DefaultRotation;
	FRotator StartRotation;
	FRotator TargetRotation;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interface
	
	virtual void NativeInteract(AActor* Interactor) override;
	
	UFUNCTION(CallInEditor, Category = "Interaction")
	virtual void BP_Interact_Implementation(AActor* Interactor) override;

private:
	UFUNCTION(CallInEditor, Category = "Interaction")
	void ActivateLever();

	UFUNCTION(BlueprintCallable, Category = "Activation")
	void DeactivateLever();

	void UpdateRotation();

	void SwapMaterial(UMaterialInstance *NewMaterial);
};
