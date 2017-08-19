// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
	SetupDefaultComponents();
}

void AProjectile::LaunchProjectile(float Speed) {

    float Time = GetWorld()->GetTimeSeconds();

    MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    MovementComponent->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AProjectile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AProjectile::SetupDefaultComponents() {

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile_Movement"));
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision_Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch_Blast"));
	LaunchBlast->AttachTo(RootComponent);
}
