// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NimbleGiantTestHUD.generated.h"

UCLASS()
class ANimbleGiantTestHUD : public AHUD
{
	GENERATED_BODY()

public:
	ANimbleGiantTestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category = "Score")
	TSubclassOf<class UUserWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Score")
	class UUserWidget* ScoreWidget;

	UPROPERTY(EditAnywhere, Category = "End")
	TSubclassOf<class UUserWidget> EndGameWidgetClass;

	UPROPERTY(EditAnywhere, Category = "End")
	class UUserWidget* EndGameWidget;
	
	UFUNCTION(Client, Reliable)
	void ShowGameOver();
	
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

