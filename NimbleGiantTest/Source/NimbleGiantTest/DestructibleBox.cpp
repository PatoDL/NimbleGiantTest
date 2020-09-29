// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBox.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADestructibleBox::ADestructibleBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void ADestructibleBox::BeginPlay()
{
	Super::BeginPlay();

	
	
	int Color = FMath::RandRange(1, 3);
	
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

		switch (Color)
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
}

// Called every frame
void ADestructibleBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

