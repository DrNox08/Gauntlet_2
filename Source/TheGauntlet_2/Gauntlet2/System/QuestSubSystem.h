// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubSystem.generated.h"

/**
 * 
 */

//Events

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, FText, NewInstructions);

UCLASS()
class THEGAUNTLET_2_API UQuestSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	
	int32 CurrentQuestStep = 0;

	FText CurrentQuestInstructions = FText::GetEmpty();

	UPROPERTY(Transient)
	TObjectPtr<UDataTable> CurrentQuestTable;

	public:

	UPROPERTY(BlueprintAssignable, Category = "QuestSubSystem")
	FOnQuestUpdated OnQuestUpdated;

	UFUNCTION(BlueprintCallable, Category = "QuestSubSystem")
	void StartQuest(TSoftObjectPtr<UDataTable> QuestTable);

	UFUNCTION(BlueprintCallable, Category = "QuestSubSystem")
	void UpdateQuest();

	UFUNCTION(BlueprintCallable, Category = "QuestSubSystem")
	void ResetQuestStep() { CurrentQuestStep = 0; }
	

	UFUNCTION(blueprintCallable, Category = "QuestSubSystem")
	FText GetCurrentQuestInstructions() const { return CurrentQuestInstructions; }
	
};
