// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbleGiantTestPlayerState.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
#include "NimbleGiantTestHUD.h"

void ANimbleGiantTestPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	AActor* TheOwner = GetOwner();
	
	if(TheOwner != nullptr)
		OnScoreUpdate();
}

void ANimbleGiantTestPlayerState::OnScoreUpdate_Implementation() const
{
	
	//PC->GetHUD<ANimbleGiantTestHUD>()
}

void ANimbleGiantTestPlayerState::AddScore_Implementation(int ScoreToAdd)
{
	Score += ScoreToAdd;
}