// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleBox.h"
#include "GameFramework/GameMode.h"
#include "NimbleGiantTestGameMode.generated.h"

UCLASS(minimalapi)
class ANimbleGiantTestGameMode : public AGameMode
{
	GENERATED_BODY()

	
	
public:
	ANimbleGiantTestGameMode();


	void StartMatch() override;

	UFUNCTION(Server, Reliable)
	void ResetGame();
	
	void RestartPlayer(AController* NewPlayer) override;
};