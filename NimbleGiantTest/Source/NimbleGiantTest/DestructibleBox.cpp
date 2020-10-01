// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBox.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADestructibleBox::ADestructibleBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMeshComponent"));

	//CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	// Set as root component
	RootComponent = CollisionComp;

	StaticMeshComponent->SetupAttachment(RootComponent);

	
	
	
}

// Called when the game starts or when spawned
void ADestructibleBox::BeginPlay()
{
	Super::BeginPlay();

	
	
	colorValue = FMath::RandRange(1, 3);
	
	AActor * rootComponent = GetOwner();

	UActorComponent* comp = GetComponentByClass(UStaticMeshComponent::StaticClass());

	UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(comp);

	
	
	if (SM != nullptr)
	{
		/*FHashedMaterialParameterInfo HashedMaterialParameterInfo;
		HashedMaterialParameterInfo.Name = FString("DiffuseColor");*/
		FLinearColor LinearColor;
		//SM->GetMaterial(0)->GetVectorParameterValue(HashedMaterialParameterInfo, LinearColor);
		FVector Vector;

		switch (colorValue)
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
		
		SM->SetVectorParameterValueOnMaterials("DiffuseColor", Vector);
	}

	FVector BoxBoundsExtents = StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;
	
	DrawDebugLine(GetWorld(), GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3 + FVector::UpVector * rayMultiplier, FColor::Red, true);
	DrawDebugLine(GetWorld(), GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3 + FVector::UpVector * rayMultiplier, FColor::Red, true);
	DrawDebugLine(GetWorld(), GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::LeftVector *BoxBoundsExtents / 3 + FVector::DownVector * rayMultiplier, FColor::Red, true);
	DrawDebugLine(GetWorld(), GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3 + FVector::DownVector * rayMultiplier, FColor::Red, true);
}

// Called every frame
void ADestructibleBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int fib(int value)
{
	if (value == 1)
		return 1;
	if (value == 0)
		return 0;

	return fib(value - 2) + fib(value - 1);
}

void ADestructibleBox::CascadeDestroy(int &value, int index)
{
	bChecked = true;
	
	TArray<FHitResult> OutHits;

	for(int i=0;i<6;i++)
	{
		FHitResult OutHit;
		OutHits.Add(OutHit);
	}

	TArray<bool> Hits;

	for (int i = 0; i < 6; i++)
	{
		bool bHit = false;
		Hits.Add(bHit);
	}

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	FVector BoxBoundsExtents = StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;
	
	Hits[0] = GetWorld()->LineTraceSingleByChannel(OutHits[0], GetActorLocation() + FVector::LeftVector * BoxBoundsExtents /3, GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3 + FVector::UpVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);
	Hits[1] = GetWorld()->LineTraceSingleByChannel(OutHits[1], GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3 + FVector::UpVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);
	Hits[2] = GetWorld()->LineTraceSingleByChannel(OutHits[2], GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::LeftVector * BoxBoundsExtents / 3 + FVector::DownVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);
	Hits[3] = GetWorld()->LineTraceSingleByChannel(OutHits[3], GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3, GetActorLocation() + FVector::RightVector * BoxBoundsExtents / 3 + FVector::DownVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);
	Hits[4] = GetWorld()->LineTraceSingleByChannel(OutHits[4], GetActorLocation(), GetActorLocation() + FVector::LeftVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);
	Hits[5] = GetWorld()->LineTraceSingleByChannel(OutHits[5], GetActorLocation(), GetActorLocation() + FVector::RightVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);

	value = fib(index);
	
	for(int i=0;i<6;i++)
	{
		if(Hits[i])
		{
			ADestructibleBox* DestructibleBox = Cast<ADestructibleBox>(OutHits[i].GetActor());

			if (DestructibleBox && DestructibleBox != this)
			{
				if(DestructibleBox->colorValue == colorValue && !DestructibleBox->bChecked)
				{
					int NewVal = value;
					DestructibleBox->CascadeDestroy(NewVal, index + 1);
					value += NewVal;
				}
				else if (i == 0 || i == 1)
				{
					DestructibleBox->CascadeFall();
				}
			}
		}
	}

	Destroy();
}

void ADestructibleBox::CascadeFall()
{
	FHitResult OutHit;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), GetActorLocation() + FVector::UpVector * rayMultiplier, ECC_Visibility, CollisionQueryParams);

	if(bHit)
	{
		ADestructibleBox* DestructibleBox = Cast<ADestructibleBox>(OutHit.GetActor());

		if(DestructibleBox)
		{
			DestructibleBox->CascadeFall();
		}
	}
}