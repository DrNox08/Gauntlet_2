// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet2/Actors/PivotalOrbiter.h"

// Sets default values
APivotalOrbiter::APivotalOrbiter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PivotRoot = CreateDefaultSubobject<USceneComponent>("PivotRoot");
	RootComponent = PivotRoot;
}

// Called when the game starts or when spawned
void APivotalOrbiter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APivotalOrbiter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bActive) return;

	// Local rotation
	const float DeltaYaw = AngularSpeedDeg * DeltaTime;
	AddActorLocalRotation(FRotator(0.f, DeltaYaw, 0.f), false, nullptr, ETeleportType::None);
}

void APivotalOrbiter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	RebuildSlotsAndAttachPlatforms();
}

void APivotalOrbiter::RebuildSlotsAndAttachPlatforms()
{
	ClearSlots();

	const int32 N = Platforms.Num();
	if (N <= 0 || !PivotRoot)
	{
		return;
	}

	OrbitSlots.Reserve(N);

	for (int32 i = 0; i < N; ++i)
	{
		const FString SlotName = FString::Printf(TEXT("OrbitSlot_%d"), i);
		USceneComponent* Slot = NewObject<USceneComponent>(this, *SlotName);

		if (!Slot)
		{
			continue;
		}

		Slot->SetupAttachment(PivotRoot);
		Slot->RegisterComponent();

		// Circle positioning in local space XY (Z=0).
		const float AngleDeg = (360.f * i) / float(N);
		const float AngleRad = FMath::DegreesToRadians(AngleDeg);

		const float X = Radius * FMath::Cos(AngleRad);
		const float Y = Radius * FMath::Sin(AngleRad);

		Slot->SetRelativeLocation(FVector(X, Y, 0.f));
		Slot->SetRelativeRotation(FRotator::ZeroRotator);

		OrbitSlots.Add(Slot);

		// Attach platforms
		AActor* Platform = Platforms[i];
		if (!Platform || Platform == this)
		{
			continue;
		}

		if (Platform->GetWorld() != GetWorld())
		{
			continue;
		}

		// Attacch and bring the platform to slot position
		Platform->AttachToComponent(Slot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void APivotalOrbiter::ClearSlots()
{
	for (USceneComponent* Slot : OrbitSlots)
	{
		if (Slot && !Slot->IsBeingDestroyed()) Slot->DestroyComponent();
	}

	OrbitSlots.Reset();
}

void APivotalOrbiter::BP_Activate_Implementation()
{
	NativeActivate();
}

void APivotalOrbiter::BP_Deactivate_Implementation()
{
	NativeDeactivate();
}
