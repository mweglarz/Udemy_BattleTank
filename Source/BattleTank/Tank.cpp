// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire() {

    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

    if (!ensure(Barrel) || !isReloaded) return;

    UE_LOG(LogTemp, Warning, TEXT("isReloaded ? %d"), isReloaded);

    // Spawn a projectile at the socket location of the barrel
    FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator Rotator = Barrel->GetSocketRotation(FName("Projectile"));

    auto SpawnedActor = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotator);
    if (!ensure(SpawnedActor)) return;
    SpawnedActor->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
    Super::BeginPlay();
}
