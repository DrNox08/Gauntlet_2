// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGauntlet_2Character.h"
#include "Gauntlet2/Actor_Components/InteractionComponent.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEGAUNTLET_2_API AMainCharacter : public ATheGauntlet_2Character
{
	GENERATED_BODY()

	AMainCharacter();

	public:

	//Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components")
	UInteractionComponent* InteractionComponent;

	// Additional Input: Interact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;

	// Additional Input: Interact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* PauseAction;


	protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	
	void TryInteract();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pause")
	void DoPause();
};
