// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

#include <string>

#include "NimbleGiantTestPlayerState.h"
#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore()
{
	const ANimbleGiantTestPlayerState* ActualState = GetOwningPlayerState<ANimbleGiantTestPlayerState>();
	if(ActualState)
	{
		ScoreText->SetText(FText::FromString(FString("Your score is: ")+FString::SanitizeFloat(ActualState->GetScore(), 0)));
	}
		
}