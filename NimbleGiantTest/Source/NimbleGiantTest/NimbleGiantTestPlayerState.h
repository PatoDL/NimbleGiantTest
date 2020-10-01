// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NimbleGiantTestPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NIMBLEGIANTTEST_API ANimbleGiantTestPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void AddScore(int ScoreToAdd)
	{
		Score += ScoreToAdd;
	}
};
