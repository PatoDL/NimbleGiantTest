// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxSpawner.generated.h"

UCLASS()
class NIMBLEGIANTTEST_API ABoxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxSpawner();

	UPROPERTY(EditAnywhere, Category = Implementation)
	TSubclassOf<class ADestructibleBox> Box;
	
	UPROPERTY(EditAnywhere, Category=Implementation)
	int32 MaxAmount;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* CollisionComp;

	TArray<ADestructibleBox*> BoxArray;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void SpawnPyramid();


	UFUNCTION(Server, Reliable)
	void SetBoxColors();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class UBoxComponent* GetCollisionComponent() const { return CollisionComp; }
};
