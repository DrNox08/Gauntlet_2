// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet2/Actors/Lever.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ALever::ALever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(RootComponent);
	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();

	DefaultRotation = LeverMesh->GetRelativeRotation();

	//Set material to deactivated at start
	SwapMaterial(DeactivatedMaterial);

	//Get Activable interface from linked actor
	if (ActorToControl)
	{
		Activable = Cast<IActivable>(ActorToControl);
	}
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALever::NativeInteract(AActor* Interactor)
{
	ActivateLever();
}

void ALever::BP_Interact_Implementation(AActor* Interactor)
{
	NativeInteract(Interactor);
}

void ALever::ActivateLever()
{
	if (bIsInteracted) return;

	//Set material to activated
	SwapMaterial(ActivatedMaterial);

	bIsInteracted = true;
	bIsReturning = false;

	StartRotation = LeverMesh->GetRelativeRotation();
	TargetRotation = StartRotation;
	TargetRotation.Pitch = -StartRotation.Pitch;

	ElapsedTime = 0.0f;

	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ALever::UpdateRotation,
		0.01f,
		true
	);
}

void ALever::DeactivateLever()
{
	bIsReturning = true;


	StartRotation = LeverMesh->GetRelativeRotation();
	TargetRotation = DefaultRotation;
	TargetRotation.Normalize();

	ElapsedTime = 0.0f;

	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ALever::UpdateRotation,
		0.01f,
		true
	);
}

void ALever::UpdateRotation()
{
	const float Step = 0.01f;
	ElapsedTime += Step;

	float Alpha = ElapsedTime / AnimationDuration;

	const FQuat ResultQuat = FQuat::Slerp(
		StartRotation.Quaternion(),
		TargetRotation.Quaternion(),
		Alpha);

	LeverMesh->SetRelativeRotation(ResultQuat);

	if (Alpha >= 1.0f)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);

		if (!bIsReturning)
		{
			//Activate linked actor
			if (ActorToControl && ActorToControl->GetClass()->ImplementsInterface(UActivable::StaticClass()))
			{
				IActivable::Execute_BP_Activate(ActorToControl);
			}


			//Start hold timer
			GetWorldTimerManager().ClearTimer(HoldTimerHandle);
			GetWorldTimerManager().SetTimer(
				HoldTimerHandle,
				this,
				&ALever::DeactivateLever,
				HoldDuration,
				false
			);
		}
		else
		{
			//Deactivate linked actor
			if (ActorToControl && ActorToControl->GetClass()->ImplementsInterface(UActivable::StaticClass()))
			{
				IActivable::Execute_BP_Deactivate(ActorToControl);
			}
			bIsInteracted = false;
			bIsReturning = false;
			//set material to deactivated
			SwapMaterial(DeactivatedMaterial);
		}
	}
}

void ALever::SwapMaterial(UMaterialInstance* NewMaterial)
{
	if (!IsValid(NewMaterial))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Lever: Material is not valid"), true, true,
		                                  FLinearColor::Red, 2.0f);
		return;
	}
	LeverMesh->SetMaterial(0, NewMaterial);
}
