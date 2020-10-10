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

	TArray<ADestructibleBox*> BoxArray;
	
public:
	ANimbleGiantTestGameMode();

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

	UFUNCTION(Server, Reliable)
	void EndGame();

	UFUNCTION(Server, Reliable)
	void ResetGame();

	
};