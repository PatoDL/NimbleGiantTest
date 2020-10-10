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

	TArray<class ADestructibleBox*> BoxArray;
public:
	UFUNCTION(NetMulticast, Reliable)
	void PauseGamePlay(bool ShouldPause);

	UFUNCTION(NetMulticast, Reliable)
	void CallRestartGame();

	UFUNCTION(NetMulticast, Reliable)
	void ResetPlayers();

	UFUNCTION()
	void AddBox(ADestructibleBox* box);

	UFUNCTION()
	FORCEINLINE int32 GetBoxCount()
	{
		return BoxArray.Num();
	}

	UFUNCTION()
	FORCEINLINE ADestructibleBox* GetBox(int32 Index)
	{
		return BoxArray[Index];
	}

	UFUNCTION()
	void RemoveBox(ADestructibleBox* Box);

	UFUNCTION(NetMulticast, Reliable)
	void EndGame();
};
