// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimbleGiantTestHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "ScoreWidget.h"
#include "EndGameWidget.h"
#include "NimbleGiantTestGameState.h"

ANimbleGiantTestHUD::ANimbleGiantTestHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void ANimbleGiantTestHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void ANimbleGiantTestHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass != nullptr)
	{
		ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);

		if (ScoreWidget != nullptr)
		{
			ScoreWidget->AddToViewport();
		}
	}

	if(EndGameWidgetClass != nullptr)
	{
		EndGameWidget = CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass);

		if (EndGameWidget != nullptr)
		{
			EndGameWidget->AddToViewport();
			EndGameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ANimbleGiantTestHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UScoreWidget* NewScoreWidget = Cast<UScoreWidget>(ScoreWidget);

	if(NewScoreWidget != nullptr)
	{
		NewScoreWidget->UpdateScore();
	}
}

void ANimbleGiantTestHUD::ShowGameOver_Implementation()
{
	if(EndGameWidget != nullptr && EndGameWidget->GetVisibility() != ESlateVisibility::Visible)
	{
		EndGameWidget->SetVisibility(ESlateVisibility::Visible);
		UEndGameWidget* NewEndGameWidget = Cast<UEndGameWidget>(EndGameWidget);

		if (NewEndGameWidget != nullptr)
		{
			NewEndGameWidget->GetScores();
			NewEndGameWidget->DrawScores();
		}
	}
		
	if (ScoreWidget != nullptr)
		ScoreWidget->SetVisibility(ESlateVisibility::Hidden);
	
	GetWorld()->GetGameState<ANimbleGiantTestGameState>()->PauseGamePlay(true);
}
