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
private:
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable)
	void AddScore(int ScoreToAdd);
	
	void OnRep_Score() override;
	
	UFUNCTION(Client, Reliable)
	void OnScoreUpdate() const;

	UFUNCTION(Server, Reliable)
	void AskForRestart();
};
