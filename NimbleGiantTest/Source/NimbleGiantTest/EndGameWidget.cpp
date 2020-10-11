// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "NimbleGiantTestPlayerState.h"
#include "Components/VerticalBoxSlot.h"
#include "NimbleGiantTestGameState.h"
#include "Styling/SlateColor.h"

void UEndGameWidget::GetScores()
{	
	TArray<int32> GotScores = GetWorld()->GetGameState<ANimbleGiantTestGameState>()->GetScores();
	for(int32 i = 0;i < GotScores.Num();i++)
	{
		Scores.Add(GotScores[i]);
	}
}

void UEndGameWidget::DrawScores()
{
	float bHasAlreadyShownTheirScore = false;
	for (int32 i = 0; i < Scores.Num(); i++)
	{
		UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		if (Scores[i] == GetOwningPlayerState<ANimbleGiantTestPlayerState>()->GetScore() && !bHasAlreadyShownTheirScore)
		{
			FString String("This is you -> ");
			if (GetOwningPlayerState<ANimbleGiantTestPlayerState>()->GetNetMode() == NM_Standalone)
			{
				String = "Your Final Score: ";
			}
			TextBlock->SetText(FText::FromString(String + FString::SanitizeFloat(Scores[i], 0)));
			bHasAlreadyShownTheirScore = true;
		}
		else
		{
			TextBlock->SetText(FText::FromString(FString::SanitizeFloat(Scores[i], 0)));
		}
		FSlateFontInfo FontInfo;
		FontInfo = TextBlock->Font;
		FontInfo.Size = 50;
		TextBlock->SetFont(FontInfo);
		const FSlateColor SlateColor(FLinearColor::Black);
		TextBlock->SetColorAndOpacity(SlateColor);
		TextBlock->SynchronizeProperties();
		ScoresBox->AddChildToVerticalBox(TextBlock);
		UVerticalBoxSlot* TextBlockSlot = Cast<UVerticalBoxSlot>(TextBlock->Slot);
		if (TextBlockSlot != nullptr)
		{
			TextBlockSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);
		}
	}
}

void UEndGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RestartButton->OnClicked.AddDynamic(this, &ThisClass::CallRestartGame);
}

void UEndGameWidget::CallRestartGame_Implementation()
{
	GetOwningPlayerState<ANimbleGiantTestPlayerState>()->AskForRestart();
}
