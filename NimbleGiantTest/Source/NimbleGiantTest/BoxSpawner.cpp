// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"
#include "DestructibleBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NimbleGiantTestGameState.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority || GetNetMode() != NM_DedicatedServer)
	{
		SpawnPyramid();
		SetBoxColors();
	}
}

void ABoxSpawner::SpawnPyramid_Implementation()
{
	FVector InitialPosition = GetActorLocation();

	ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();
	
	while (BaseBoxAmount > 0)
	{
		for (int i = BaseBoxAmount; i > 0; i--)
		{
			//GetWorld()->SpawnActor(Box, Loc, Rot);
			FTransform Transform;
			Transform.SetLocation(GetActorLocation());
			Transform.SetRotation(GetActorRotation().Quaternion());

			ADestructibleBox* NewBox = GetWorld()->SpawnActor<ADestructibleBox>(Box, Transform);
			if (GameState)
				GameState->AddBox(NewBox);
			FVector ActualLocation = GetActorLocation();
			ActualLocation.Y += 100;
			SetActorLocation(ActualLocation);
		}

		InitialPosition.Z += 100;
		InitialPosition.Y += 50;
		SetActorLocation(InitialPosition);
		BaseBoxAmount--;
	}
}

void ABoxSpawner::SetBoxColors_Implementation()
{
	ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();

	if (GameState)
	{
		for (int i = 0; i < GameState->GetBoxCount(); i++)
		{
			GameState->GetBox(i)->ColorValue = FMath::RandRange(1, 3);
			if(GetNetMode() != NM_DedicatedServer)
			{
				GameState->GetBox(i)->OnColorUpdate();
			}
		}
	}
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

