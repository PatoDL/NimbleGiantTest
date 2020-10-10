// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestGameState.h"

#include "NimbleGiantTestPlayerState.h"
#include "NimbleGiantTestHUD.h"
#include "NimbleGiantTestGameMode.h"

void ANimbleGiantTestGameState::UpdateHUD_Implementation()
{
	if(GetLocalRole() < ROLE_Authority || GetNetMode() != NM_DedicatedServer)
	{
		for (int i = 0; i < PlayerArray.Num(); i++)
		{
			AActor* O = PlayerArray[i]->GetOwner();
			APlayerController* PlayerController = Cast<APlayerController>(O);
			if (PlayerController != nullptr)
				PlayerController->GetHUD<ANimbleGiantTestHUD>()->ShowGameOver();
		}
	}
}

void ANimbleGiantTestGameState::ResetPlayers_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i = 0; i < PlayerArray.Num(); i++)
		{
			APlayerController* PlayerController = Cast<APlayerController>(PlayerArray[i]->GetOwner());
			PlayerController->ClientTravel("127.0.0.1", ETravelType::TRAVEL_Absolute);
		}
	}
}

void ANimbleGiantTestGameState::CallRestartGame_Implementation()
{
	if(GetLocalRole()==ROLE_Authority)
	{
		GetWorld()->GetAuthGameMode<ANimbleGiantTestGameMode>()->ResetGame();
	}
}

void ANimbleGiantTestGameState::PauseGamePlay_Implementation(bool ShouldPause)
{
	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		AActor* O = PlayerArray[i]->GetOwner();
		APlayerController* PC = Cast<APlayerController>(O);
		if (PC != nullptr)
		{
			if (ShouldPause)
			{
				FInputModeUIOnly InputModeUIOnly;
				PC->SetInputMode(InputModeUIOnly);
				PC->bShowMouseCursor = true;
			}
			else
			{
				FInputModeGameOnly InputModeGameOnly;
				PC->SetInputMode(InputModeGameOnly);
				PC->bShowMouseCursor = false;
				/*PC->EnableInput(PC);
				PC->bShowMouseCursor = true;*/
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

void ANimbleGiantTestGameState::EndGame_Implementation()
{
	UpdateHUD();
}
