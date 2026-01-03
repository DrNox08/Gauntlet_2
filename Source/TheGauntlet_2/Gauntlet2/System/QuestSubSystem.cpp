// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet2/System/QuestSubSystem.h"

#include "QuestTable.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

void UQuestSubSystem::StartQuest(TSoftObjectPtr<UDataTable> QuestTable)
{
	CurrentQuestTable = QuestTable.LoadSynchronous();
	if (CurrentQuestTable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestSubSystem: Failed to load quest table."));
		return; // Early exit if table failed to load
	}

	UpdateQuest();
}

void UQuestSubSystem::UpdateQuest()
{
	CurrentQuestStep++;

	//Setup strings
	FString RowString = TEXT("Step_");
	RowString += FString::FromInt(CurrentQuestStep);
	FName RowName(*RowString);
	FQuestDetailsRow* QuestRow = CurrentQuestTable->FindRow<FQuestDetailsRow>(RowName, TEXT("UpdateQuest"));

	if (!QuestRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestSubSystem: No more quest steps found."));
		return; // Early exit if no more rows
	}

	//Use data from row
	CurrentQuestInstructions = QuestRow->QuestInstructions;
	//Call event for UI update
	OnQuestUpdated.Broadcast(CurrentQuestInstructions);

	//Play sound if valid
	if (!QuestRow->Sound.IsNull())
	{
		const TSoftObjectPtr<USoundBase> SoundRef = QuestRow->Sound;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SoundRef.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([this, SoundRef]()
			{
				if (USoundBase* LoadedSound = SoundRef.Get())
				{
					UGameplayStatics::PlaySound2D(GetWorld(), LoadedSound);
				}
			})

		);
	}
}
