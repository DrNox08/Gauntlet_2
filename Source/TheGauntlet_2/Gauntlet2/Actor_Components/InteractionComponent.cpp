// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "GameFramework/Character.h"
#include "Gauntlet2/Interfaces/Interactable.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


TArray<AActor*> UInteractionComponent::InteractionTracedObjects(const float Distance, const float Radius)
{
	FVector EndTrace = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() *
		DistanceInteraction;

	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> Hits;
	TArray<AActor*> ActorsFound;

	if (!IsValid(GetWorld()))
	{
		return ActorsFound;
	}

	FVector Start = this->GetOwner()->GetActorLocation();
	FVector End = Start + this->GetOwner()->GetActorForwardVector() * 500.f;
	float radius = 300;
	UKismetSystemLibrary::SphereTraceMultiForObjects(
		this->GetOwner()->GetWorld(),
		this->GetOwner()->GetActorLocation(),
		EndTrace,
		RadiusInteraction,
		ObjectTypesToInteract,
		false,
		ActorsToIgnore,
		bDebugInteraction ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		Hits,
		true
	);

	for (FHitResult HitResults : Hits)
	{
		ActorsFound.AddUnique(HitResults.GetActor());
	}

	ClosestActor = nullptr;
	float MinDistance = FLT_MAX;

	for (AActor* Actor : ActorsFound)
	{
		float Dist = FVector::Dist(this->GetOwner()->GetActorLocation(), Actor->GetActorLocation());
		if (Dist < MinDistance)
		{
			MinDistance = Dist;
			ClosestActor = Actor;
		}
	}


	return ActorsFound;
}

void UInteractionComponent::Interact()
{
	AActor* Interactor = GetOwner();
	if (!IsValid(Interactor)) return;

	ACharacter* Character = Cast<ACharacter>(Interactor);
	if (!IsValid(Character)) return;

	if (IsValid(ClosestActor) && ClosestActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_BP_Interact(ClosestActor, Interactor);
	}
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bSocketOccupied)
	{
		InteractionTracedObjects(DistanceInteraction, RadiusInteraction);
	}
	
}
