// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGauntlet_2PlayerController.h"
#include "GauntletController.generated.h"

/**
 * 
 */
UCLASS()
class THEGAUNTLET_2_API AGauntletController : public ATheGauntlet_2PlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
};
