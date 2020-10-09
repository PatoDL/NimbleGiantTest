// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestGameState.h"
#include "NimbleGiantTestPlayerState.h"
#include "NimbleGiantTestHUD.h"

void ANimbleGiantTestGameState::UpdateHUD_Implementation()
{
	if(GetLocalRole() < ROLE_Authority)
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
