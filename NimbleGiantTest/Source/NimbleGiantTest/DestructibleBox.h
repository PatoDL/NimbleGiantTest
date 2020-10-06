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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing = OnRep_SwitchColor)
	uint16 ColorValue;

	UPROPERTY(EditAnywhere, Category = Implementation)
	float RayMultiplier;

	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;
	
	bool bBoxAlreadyCheckedInCascade;

	void OnColorUpdate();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class UBoxComponent* GetCollisionComponent() const { return CollisionComponent; }
	void CascadeDestroy(uint32 &ScoreToAdd, uint16 FibonacciIndex);

	UFUNCTION(Server, Reliable)
	void StartBox();

	UFUNCTION()
	void OnRep_SwitchColor();
};
