// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimbleGiantTestGameMode.h"
#include "NimbleGiantTestHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "NimbleGiantTestPlayerState.h"
#include "NimbleGiantTestGameState.h"
#include "Kismet/GameplayStatics.h"
#include "BoxSpawner.h"

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

void ANimbleGiantTestGameMode::StartMatch()
{
	Super::StartMatch();

	AActor* BoxSpawnerActor = UGameplayStatics::GetActorOfClass(this, ABoxSpawner::StaticClass());

	if(BoxSpawnerActor != nullptr)
	{
		ABoxSpawner* BoxSpawner = Cast<ABoxSpawner>(BoxSpawnerActor);

		BoxSpawner->SpawnPyramid();
		BoxSpawner->SetBoxColors();
	}
}

void ANimbleGiantTestGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	APlayerController* PlayerController = Cast<APlayerController>(NewPlayer);
	
	if (PlayerController != nullptr)
	{
		PlayerController->ClientTravel("IPADDRESS", ETravelType::TRAVEL_Absolute);
	}
}

void ANimbleGiantTestGameMode::ResetGame_Implementation()
{
	//GetWorld()->ServerTravel("?Restart", true);
	UGameplayStatics::OpenLevel(this, "?", true, "listen");
	GetGameState<ANimbleGiantTestGameState>()->PauseGamePlay(false);
}
