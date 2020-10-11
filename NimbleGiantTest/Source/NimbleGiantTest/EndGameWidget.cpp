// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "NimbleGiantTestPlayerState.h"
#include "Components/VerticalBoxSlot.h"
#include "Styling/SlateColor.h"

void UEndGameWidget::GetScores(TArray<float> GotScores)
{
	for(int i = 0;i < GotScores.Num();i++)
	{
		Scores.Add(GotScores[i]);
	}
}

void UEndGameWidget::DrawScores()
{
	for (int i = 0; i < Scores.Num(); i++)
	{
		UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		TextBlock->SetText(FText::FromString(FString::SanitizeFloat(Scores[i])));
		FSlateFontInfo FontInfo;
		FontInfo = TextBlock->Font;
		FontInfo.Size = 50;
		TextBlock->SetFont(FontInfo);
		const FSlateColor SlateColor(FLinearColor::Black);
		TextBlock->SetColorAndOpacity(SlateColor);
		TextBlock->SynchronizeProperties();
		ScoresBox->AddChildToVerticalBox(TextBlock);
		UVerticalBoxSlot* TextBlockSlot = Cast<UVerticalBoxSlot>(TextBlock->Slot);
		if(TextBlockSlot)
		{
			TextBlockSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		}
	}
}

void UEndGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RestartButton->OnClicked.AddDynamic(this, &ThisClass::CallRestartGame);
	TArray<float> asd;

	for(int i=0;i< 4;i++)
	{
		asd.Add(i);
	}

	GetScores(asd);
}

void UEndGameWidget::CallRestartGame_Implementation()
{
	GetOwningPlayerState<ANimbleGiantTestPlayerState>()->AskForRestart();
}
