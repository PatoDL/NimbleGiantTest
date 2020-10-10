// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestGameState.h"

#include "NimbleGiantTestPlayerState.h"
#include "NimbleGiantTestHUD.h"
#include "NimbleGiantTestGameMode.h"

void ANimbleGiantTestGameState::ResetPlayers_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		for (int i = 0; i < PlayerArray.Num(); i++)
		{
			AController* PC = Cast<AController>(PlayerArray[i]->GetOwner());
			GetWorld()->GetAuthGameMode<ANimbleGiantTestGameMode>()->RestartPlayer(PC);
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
	if (GetLocalRole() < ROLE_Authority || GetNetMode() != NM_DedicatedServer)
	{
		for (int i = 0; i < PlayerArray.Num(); i++)
		{
			AActor* O = PlayerArray[i]->GetOwner();
			APlayerController* PC = Cast<APlayerController>(O);
			if (PC != nullptr)
				PC->GetHUD<ANimbleGiantTestHUD>()->ShowGameOver();
		}
	}
}
