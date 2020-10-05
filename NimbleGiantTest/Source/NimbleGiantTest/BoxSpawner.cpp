// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"
#include "DestructibleBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABoxSpawner::ABoxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();

	FVector InitialPosition = GetActorLocation();

	while(MaxAmount > 0)
	{
		for (int i = MaxAmount; i > 0; i--)
		{
			//GetWorld()->SpawnActor(Box, Loc, Rot);
			FTransform Transform;
			Transform.SetLocation(GetActorLocation());
			Transform.SetRotation(GetActorRotation().Quaternion());

			ADestructibleBox* NewBox = GetWorld()->SpawnActorDeferred<ADestructibleBox>(Box, Transform);
			NewBox->ColorValue = FMath::RandRange(1, 3);
			UGameplayStatics::FinishSpawningActor(NewBox, Transform);
			FVector ActualLocation = GetActorLocation();
			ActualLocation.Y += 100;
			SetActorLocation(ActualLocation);
		}
		
		InitialPosition.Z += 100;
		InitialPosition.Y += 50;
		SetActorLocation(InitialPosition);
		MaxAmount--;
	}

	Destroy();
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

