// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "NimbleGiantTestPlayerState.h"

void UEndGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RestartButton->OnClicked.AddDynamic(this, &ThisClass::CallRestartGame);
}

void UEndGameWidget::CallRestartGame_Implementation()
{
	GetOwningPlayerState<ANimbleGiantTestPlayerState>()->AskForRestart();
}
