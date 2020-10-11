// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestGameState.h"

#include "NimbleGiantTestPlayerState.h"
#include "NimbleGiantTestHUD.h"
#include "NimbleGiantTestGameMode.h"
#include "Algo/Reverse.h"

void ANimbleGiantTestGameState::ResetPlayers_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int32 i = 0; i < PlayerArray.Num(); i++)
		{
			APlayerController* PlayerController = Cast<APlayerController>(PlayerArray[i]->GetOwner());
			if(PlayerController != nullptr)
				PlayerController->ClientTravel("127.0.0.1", ETravelType::TRAVEL_Absolute);
		}
	}
}

void ANimbleGiantTestGameState::CallRestartGame_Implementation()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		GetWorld()->GetAuthGameMode<ANimbleGiantTestGameMode>()->ResetGame();
	}
}

void ANimbleGiantTestGameState::PauseGamePlay_Implementation(bool ShouldPause)
{
	for (int32 i = 0; i < PlayerArray.Num(); i++)
	{
		AActor* O = PlayerArray[i]->GetOwner();
		APlayerController* PlayerController = Cast<APlayerController>(O);
		if (PlayerController != nullptr)
		{
			if (ShouldPause)
			{
				FInputModeUIOnly InputModeUIOnly;
				PlayerController->SetInputMode(InputModeUIOnly);
				PlayerController->bShowMouseCursor = true;
			}
			else
			{
				FInputModeGameOnly InputModeGameOnly;
				PlayerController->SetInputMode(InputModeGameOnly);
				PlayerController->bShowMouseCursor = false;
			}
		}
	}
}

void ANimbleGiantTestGameState::AddBox(ADestructibleBox* Box)
{
	BoxArray.Add(Box);
}

void ANimbleGiantTestGameState::RemoveBox(ADestructibleBox* Box)
{
	BoxArray.Remove(Box);
}

TArray<int32> ANimbleGiantTestGameState::GetScores()
{
	TArray<int32> Scores;

	for (int32 i = 0; i < PlayerArray.Num(); i++)
	{
		Scores.Add(PlayerArray[i]->GetScore());
	}

	Scores.Sort();

	Algo::Reverse(Scores);
	
	return Scores;
}

void ANimbleGiantTestGameState::EndGame_Implementation()
{
	if (GetLocalRole() < ROLE_Authority || GetNetMode() != NM_DedicatedServer)
	{	
		for (int32 i = 0; i < PlayerArray.Num(); i++)
		{
			AActor* ActualActor = PlayerArray[i]->GetOwner();
			APlayerController* PlayerController = Cast<APlayerController>(ActualActor);
			if (PlayerController != nullptr)
				PlayerController->GetHUD<ANimbleGiantTestHUD>()->ShowGameOver();
		}
	}
}
