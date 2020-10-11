// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimbleGiantTestProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "DestructibleBox.h"
#include "Kismet/GameplayStatics.h"
#include "NimbleGiantTestCharacter.h"
#include "NimbleGiantTestGameState.h"
#include "NimbleGiantTestPlayerState.h"

ANimbleGiantTestProjectile::ANimbleGiantTestProjectile() 
{
	bReplicates = true;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &ANimbleGiantTestProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	if (GetLocalRole() == ROLE_Authority)
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &ANimbleGiantTestProjectile::OnHit);
	}
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ANimbleGiantTestProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics() && GetLocalRole() == ROLE_Authority)
	{
		ADestructibleBox* DestructibleBox = Cast<ADestructibleBox>(OtherActor);

		if(DestructibleBox != nullptr)
		{
			uint32 ScoreToAdd = 0;
			uint16 FibonacciIndex = 1;
			DestructibleBox->CascadeDestroy(ScoreToAdd, FibonacciIndex);
			
			ANimbleGiantTestCharacter* Character = Cast<ANimbleGiantTestCharacter>(GetOwner());
			Character->GetPlayerState<ANimbleGiantTestPlayerState>()->AddScore(ScoreToAdd);

			if(GetNetMode() != NM_DedicatedServer)
			{
				ANimbleGiantTestGameState* GameState = GetWorld()->GetGameState<ANimbleGiantTestGameState>();
				if (GameState->GetBoxCount() == 0)
				{
					GameState->EndGame();
				}
			}
		}
		Destroy();
	}
}