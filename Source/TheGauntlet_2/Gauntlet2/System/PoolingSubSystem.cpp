// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet2/System/PoolingSubSystem.h"

void UPoolingSubSystem::AddToPool(TSubclassOf<AActor> ActorClassToPool, int32 InitialSize)
{
	if (!GetWorld()) return;
	if (!IsValid(ActorClassToPool)) return;

	if (ActorClassToPool->ImplementsInterface(UPoolable::StaticClass()) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("PoolingSubSystem: Actor class does not implement IPoolable interface"));
		return;
	}

	FPoolItem PoolToGenerate;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < InitialSize; i++)
	{
		AActor* ActorRef = GetWorld()->SpawnActor<AActor>(ActorClassToPool, SpawnParams);

		ActorRef->SetActorHiddenInGame(true);
		ActorRef->SetActorEnableCollision(false);

		PoolToGenerate.InactiveObjects.AddUnique(ActorRef);
	}

	PoolMap.Add(ActorClassToPool, PoolToGenerate);
}

TScriptInterface<IPoolable> UPoolingSubSystem::GetPooledObject(TSubclassOf<AActor> ActorClassToPool)
{
	if (!GetWorld()) return nullptr;
	if (!IsValid(ActorClassToPool)) return nullptr;
	if (!PoolMap.Contains(ActorClassToPool)) return nullptr;

	FPoolItem* PoolItem = PoolMap.Find(ActorClassToPool);

	TScriptInterface<IPoolable> ActorToGet;

	//Check if there are inactive objects, else spawn a new one
	if (PoolItem->InactiveObjects.IsEmpty())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ActorToGet = GetWorld()->SpawnActor<AActor>(ActorClassToPool, SpawnParams);

		PoolItem->ActiveObjects.AddUnique(ActorToGet);
	}
	else //Get the first inactive object
	{
		ActorToGet = PoolItem->InactiveObjects[0];
		PoolItem->InactiveObjects.Remove(ActorToGet);
		PoolItem->ActiveObjects.AddUnique(ActorToGet);
	}

	return ActorToGet;
}

void UPoolingSubSystem::ReturnPooledObject(TScriptInterface<IPoolable> PooledObject,
	TSubclassOf<AActor> ActorClassToRepool)
{
	if (!GetWorld()) return;
	if (!IsValid(ActorClassToRepool)) return;
	if (!PoolMap.Contains(ActorClassToRepool)) return;

	FPoolItem* PoolItem = PoolMap.Find(ActorClassToRepool);

	if (!PoolItem->ActiveObjects.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("PoolingSubSystem: Trying to repool an object that is never been pooled"));
	}

	PoolItem->ActiveObjects.Remove(PooledObject);
	PoolItem->InactiveObjects.AddUnique(PooledObject);
}


