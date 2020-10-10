// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NimbleGiantTestGameState.generated.h"

/**
 * 
 */
UCLASS()
class NIMBLEGIANTTEST_API ANimbleGiantTestGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void UpdateHUD();

	UFUNCTION(NetMulticast, Reliable)
	void PauseGamePlay(bool ShouldPause);

	UFUNCTION(NetMulticast, Reliable)
	void CallRestartGame();

	UFUNCTION(NetMulticast, Reliable)
	void ResetPlayers();
};
