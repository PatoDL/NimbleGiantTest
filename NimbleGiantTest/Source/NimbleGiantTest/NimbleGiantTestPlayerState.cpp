// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestPlayerState.h"

#include "NimbleGiantTestGameState.h"
#include "Net/UnrealNetwork.h"

void ANimbleGiantTestPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	AActor* TheOwner = GetOwner();
	
	if(TheOwner != nullptr)
		OnScoreUpdate();
}

void ANimbleGiantTestPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANimbleGiantTestPlayerState, RemainingBoxes);
}

void ANimbleGiantTestPlayerState::OnGameEnded_Implementation()
{	
	ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();

	if (GameState != nullptr)
	{
		GameState->EndGame();
	}
}

void ANimbleGiantTestPlayerState::AskForRestart_Implementation()
{
	ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();

	if(GameState != nullptr)
	{
		GameState->CallRestartGame();
	}
}

void ANimbleGiantTestPlayerState::OnScoreUpdate_Implementation()
{
	if (RemainingBoxes == 0)
	{
		OnGameEnded();
	}
}

void ANimbleGiantTestPlayerState::AddScore_Implementation(int ScoreToAdd)
{
	Score += ScoreToAdd;

	ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();

	if (GameState != nullptr)
	{
		RemainingBoxes = GameState->GetBoxCount();
	}
}