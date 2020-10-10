// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestPlayerState.h"

#include "NimbleGiantTestGameState.h"


void ANimbleGiantTestPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	AActor* TheOwner = GetOwner();
	
	if(TheOwner != nullptr)
		OnScoreUpdate();
}

void ANimbleGiantTestPlayerState::AskForRestart_Implementation()
{
	ANimbleGiantTestGameState* GS = GetWorld()->GetGameState<ANimbleGiantTestGameState>();

	if(GS)
	{
		GS->CallRestartGame();
	}
}

void ANimbleGiantTestPlayerState::OnScoreUpdate_Implementation() const
{
	
	//PC->GetHUD<ANimbleGiantTestHUD>()
}

void ANimbleGiantTestPlayerState::AddScore_Implementation(int ScoreToAdd)
{
	Score += ScoreToAdd;
}