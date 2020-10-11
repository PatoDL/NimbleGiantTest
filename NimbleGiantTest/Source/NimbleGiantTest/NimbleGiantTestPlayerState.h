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

	UPROPERTY(ReplicatedUsing=OnRep_Score)
	int32 RemainingBoxes = 0;
	
public:
	UFUNCTION(Server, Reliable)
	void AddScore(int ScoreToAdd);
	
	void OnRep_Score() override;
	
	UFUNCTION(Client, Reliable)
	void OnScoreUpdate();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable)
	void AskForRestart();

	UFUNCTION(Server, Reliable)
	void OnGameEnded();
};
