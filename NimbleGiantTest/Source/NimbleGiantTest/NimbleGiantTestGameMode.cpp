// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimbleGiantTestGameMode.h"
#include "NimbleGiantTestHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "NimbleGiantTestPlayerState.h"
#include "NimbleGiantTestGameState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameSession.h"

ANimbleGiantTestGameMode::ANimbleGiantTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANimbleGiantTestHUD::StaticClass();

	PlayerStateClass = ANimbleGiantTestPlayerState::StaticClass();

	GameStateClass = ANimbleGiantTestGameState::StaticClass();
}

void ANimbleGiantTestGameMode::AddBox(ADestructibleBox* Box)
{
	BoxArray.Add(Box);
}

void ANimbleGiantTestGameMode::RemoveBox(ADestructibleBox* Box)
{
	BoxArray.Remove(Box);
}

void ANimbleGiantTestGameMode::ResetGame_Implementation()
{
	if (GetMatchState() == MatchState::LeavingMap)
	{
		return;
	}
	GetWorld()->ServerTravel("?Restart", true);
	GetGameState<ANimbleGiantTestGameState>()->PauseGamePlay(false);
}

void ANimbleGiantTestGameMode::EndGame_Implementation()
{
	GetGameState<ANimbleGiantTestGameState>()->UpdateHUD();
}
