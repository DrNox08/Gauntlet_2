// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestTable.generated.h"

USTRUCT(BlueprintType)
struct FQuestDetailsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	FText QuestInstructions;

	UPROPERTY(editAnywhere, BlueprintReadOnly, Category = "Quest")
	TSoftObjectPtr<USoundBase> Sound;
	
};

