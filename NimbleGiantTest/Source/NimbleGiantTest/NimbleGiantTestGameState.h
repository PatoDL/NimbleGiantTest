// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NimbleGiantTestGameState.generated.h"

/**
 * 
 */
UCLASS()
class NIMBLEGIANTTEST_API ANimbleGiantTestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void UpdateHUD();
};
