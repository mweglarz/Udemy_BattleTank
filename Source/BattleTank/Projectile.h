// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor {
	GENERATED_BODY()

private:
    UProjectileMovementComponent* MovementComponent;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* LaunchBlast = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

    void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void SetupDefaultComponents();
	
};
