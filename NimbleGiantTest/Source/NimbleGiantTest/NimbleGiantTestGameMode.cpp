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

void ANimbleGiantTestGameMode::ResetGame_Implementation()
{
	/*if (GetMatchState() == MatchState::LeavingMap)
	{
		return;
	}
	GetWorld()->ServerTravel("?Restart", true);*/

	if(GetLocalRole() == ROLE_Authority && GetNetMode() == NM_DedicatedServer)
	{
		UGameplayStatics::OpenLevel(this, "?", true, "listen");
		GetGameState<ANimbleGiantTestGameState>()->ResetPlayers();
		GetGameState<ANimbleGiantTestGameState>()->PauseGamePlay(false);
	}
	else if(GetNetMode() != NM_DedicatedServer)
	{
		UGameplayStatics::OpenLevel(this, "?");
		GetGameState<ANimbleGiantTestGameState>()->PauseGamePlay(false);
	}
}
