// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


class IInteractable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEGAUNTLET_2_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	float DistanceInteraction = 1500.f;

	// Radius interaction distance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	float RadiusInteraction = 400.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesToInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interaction")
	bool bDebugInteraction;
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	TArray<AActor*> InteractionTracedObjects(const float Distance, const float Radius);

	// Collecting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	AActor* ClosestActor = nullptr;

	bool bSocketOccupied = false;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	//Interface
	
	UPROPERTY()
	TScriptInterface<IInteractable> InteractableObject;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
};
