// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet2/Characters/MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMainCharacter::AMainCharacter()
{
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainCharacter::TryInteract);
	}
}

void AMainCharacter::TryInteract()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Interact Pressed"), true, true, FLinearColor::Green, 2.0f);
	if (!IsValid(InteractionComponent))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("COMPONENT NOT FOUND"), true, true, FLinearColor::Green, 2.0f);
	}
	InteractionComponent->Interact();
	
}
