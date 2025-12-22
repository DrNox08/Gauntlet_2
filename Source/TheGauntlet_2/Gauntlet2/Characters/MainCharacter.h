// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGauntlet_2Character.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEGAUNTLET_2_API AMainCharacter : public ATheGauntlet_2Character
{
	GENERATED_BODY()

	public:

	// Additional Input: Interact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;


	protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void TryInteract();
};
