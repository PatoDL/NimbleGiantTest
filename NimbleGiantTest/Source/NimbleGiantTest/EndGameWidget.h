// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class NIMBLEGIANTTEST_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

	TArray<float> Scores;


protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* ScoresBox;

	void NativeOnInitialized() override;

	UFUNCTION(Server, Reliable)
	void CallRestartGame();

public:

	UFUNCTION()
		void GetScores();

	UFUNCTION()
		void DrawScores();
};
