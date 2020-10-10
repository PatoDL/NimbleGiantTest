// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBox.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "NimbleGiantTestGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "NimbleGiantTestGameState.h"

// Sets default values
ADestructibleBox::ADestructibleBox()
{
	bReplicates = true;
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComponent"));
	
	// Set as root component
	RootComponent = CollisionComponent;

	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ADestructibleBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current color.
	DOREPLIFETIME(ADestructibleBox, ColorValue);
}

void ADestructibleBox::OnColorUpdate()
{
	if (StaticMeshComponent != nullptr)
	{
		FVector Vector;

		switch (ColorValue)
		{
		case 1:
			Vector = (FVector)FColor::Blue;
			break;
		case 2:
			Vector = (FVector)FColor::Red;
			break;
		case 3:
			Vector = (FVector)FColor::Green;
			break;
		}

		StaticMeshComponent->SetVectorParameterValueOnMaterials("DiffuseColor", Vector);
	}
}

// Called when the game starts or when spawned
void ADestructibleBox::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestructibleBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

uint32 Fibonacci(uint32 Value)
{
	if (Value == 1)
		return 1;
	if (Value == 0)
		return 0;

	return Fibonacci(Value - 2) + Fibonacci(Value - 1);
}

void ADestructibleBox::CascadeDestroy(uint32 &ScoreToAdd, uint16 FibonacciIndex)
{
	bBoxAlreadyCheckedInCascade = true;
	
	TArray<FHitResult> OutHits;

	for(int i=0;i<6;i++)
	{
		FHitResult OutHit;
		OutHits.Add(OutHit);
	}

	TArray<bool> bHits;

	for (int i = 0; i < 6; i++)
	{
		bool bHit = false;
		bHits.Add(bHit);
	}

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	FVector BoxBoundsExtents = StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;
	
	bHits[0] = GetWorld()->LineTraceSingleByChannel(OutHits[0], GetActorLocation() + FVector::LeftVector * BoxBoundsExtents /3, GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3 + FVector::UpVector * RayMultiplier, ECC_Visibility, CollisionQueryParams);
	bHits[1] = GetWorld()->LineTraceSingleByChannel(OutHits[1], GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3 + FVector::UpVector * RayMultiplier, ECC_Visibility, CollisionQueryParams);
	bHits[2] = GetWorld()->LineTraceSingleByChannel(OutHits[2], GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3 + FVector::DownVector * RayMultiplier, ECC_Visibility, CollisionQueryParams);
	bHits[3] = GetWorld()->LineTraceSingleByChannel(OutHits[3], GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3 + FVector::DownVector * RayMultiplier, ECC_Visibility, CollisionQueryParams);
	bHits[4] = GetWorld()->LineTraceSingleByChannel(OutHits[4], GetActorLocation(), GetActorLocation() + FVector::LeftVector * RayMultiplier, ECC_Visibility, CollisionQueryParams);
	bHits[5] = GetWorld()->LineTraceSingleByChannel(OutHits[5], GetActorLocation(), GetActorLocation() + FVector::RightVector * RayMultiplier, ECC_Visibility, CollisionQueryParams);

	ScoreToAdd += Fibonacci(FibonacciIndex);
	
	for(int i=0;i<6;i++)
	{
		if(bHits[i])
		{
			ADestructibleBox* DestructibleBox = Cast<ADestructibleBox>(OutHits[i].GetActor());

			if (DestructibleBox && DestructibleBox != this)
			{
				if(DestructibleBox->ColorValue == ColorValue && !DestructibleBox->bBoxAlreadyCheckedInCascade)
				{
					DestructibleBox->CascadeDestroy(ScoreToAdd, FibonacciIndex + 1);
				}
			}
		}
	}


	ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();
	if(GameState)
	{
		GameState->RemoveBox(this);
		if(GameState->GetBoxCount() == 0)
		{
			GameState->EndGame();
		}
	}
	Destroy();
}

void ADestructibleBox::OnRep_SwitchColor()
{
	OnColorUpdate();
}
