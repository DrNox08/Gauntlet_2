// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Activable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UActivable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEGAUNTLET_2_API IActivable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activation")
	void BP_Activate();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Activation")
	void BP_Deactivate();

	virtual void NativeActivate() = 0;
	

	virtual void NativeDeactivate() = 0;
	
		
	
};
