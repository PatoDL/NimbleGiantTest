// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"
#include "DestructibleBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NimbleGiantTestGameMode.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
	bReplicates = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		SpawnPyramid();
		SetBoxColors();
	}
}

void ABoxSpawner::SpawnPyramid_Implementation()
{
	FVector InitialPosition = GetActorLocation();

	ANimbleGiantTestGameMode* GM = Cast<ANimbleGiantTestGameMode>(GetWorld()->GetAuthGameMode());
	
	while (MaxAmount > 0)
	{
		for (int i = MaxAmount; i > 0; i--)
		{
			//GetWorld()->SpawnActor(Box, Loc, Rot);
			FTransform Transform;
			Transform.SetLocation(GetActorLocation());
			Transform.SetRotation(GetActorRotation().Quaternion());

			ADestructibleBox* NewBox = GetWorld()->SpawnActor<ADestructibleBox>(Box, Transform);
			if (GM)
				GM->AddBox(NewBox);
			FVector ActualLocation = GetActorLocation();
			ActualLocation.Y += 100;
			SetActorLocation(ActualLocation);
		}

		InitialPosition.Z += 100;
		InitialPosition.Y += 50;
		SetActorLocation(InitialPosition);
		MaxAmount--;
	}
}

void ABoxSpawner::SetBoxColors_Implementation()
{
	ANimbleGiantTestGameMode* GM = Cast<ANimbleGiantTestGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		for (int i = 0; i < GM->GetBoxCount(); i++)
		{
			GM->GetBox(i)->ColorValue = FMath::RandRange(1, 3);
		}
	}
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

