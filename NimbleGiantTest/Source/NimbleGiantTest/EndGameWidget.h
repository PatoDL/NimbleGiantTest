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

protected:
	UPROPERTY(meta = (BindWidget))
	TArray<class UTextBlock*> Scores;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	void NativeOnInitialized() override;

	UFUNCTION(Server, Reliable)
	void CallRestartGame();
};
