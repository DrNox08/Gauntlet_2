// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gauntlet2/Interfaces/Poolable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PoolingSubSystem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPoolItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
	TArray<TScriptInterface<IPoolable>> InactiveObjects;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
	TArray<TScriptInterface<IPoolable>> ActiveObjects;
};

USTRUCT(BlueprintType)
struct FPoolStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
	FString ClassName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
	int32 ActiveCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
	int32 InactiveCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
	int32 TotalCount;
};
	

UCLASS()
class THEGAUNTLET_2_API UPoolingSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	public:

	// Pooling functions

	UFUNCTION(BlueprintCallable, Category = "ObjectPoolSubSystem")
	void AddToPool(TSubclassOf<AActor> ActorClassToPool, int32 InitialSize);

	UFUNCTION(BlueprintCallable, Category = "ObjectPoolSubSystem")
	TScriptInterface<IPoolable> GetPooledObject(TSubclassOf<AActor> ActorClassToPool);

	UFUNCTION(BlueprintCallable, Category = "ObjectPoolSubSystem")
	void ReturnPooledObject(TScriptInterface<IPoolable> PooledObject, TSubclassOf<AActor> ActorClassToRepool);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ObjectPoolSubSystem")
	TMap<TSubclassOf<AActor>, FPoolItem> PoolMap;

	UFUNCTION(BlueprintCallable, Category = "ObjectPoolSubSystem")
	TArray<FPoolStats> GetPoolStats();
private:

};
