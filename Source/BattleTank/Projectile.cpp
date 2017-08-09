// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"

// Sets default values
AProjectile::AProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile_Movement"));
    MovementComponent->bAutoActivate = false;
}

void AProjectile::LaunchProjectile(float Speed) {

    float Time = GetWorld()->GetTimeSeconds();

    MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    MovementComponent->Activate();

    UE_LOG(LogTemp, Warning, TEXT("%f: Launch projectile with speed %f"), Time, Speed);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AProjectile::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
