// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleBox.generated.h"

UCLASS()
class NIMBLEGIANTTEST_API ADestructibleBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleBox();

	UPROPERTY(EditAnywhere, Category = Data)
	int colorValue;

	UPROPERTY(EditAnywhere, Category = Implementation)
	float rayMultiplier;

	UPROPERTY(EditAnywhere, Category = Implementation)
	float Impulse;

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	
	bool bChecked;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class UBoxComponent* GetCollisionComp() const { return CollisionComp; }
	void CascadeDestroy(int &value, int index);
	void CascadeFall();
};
