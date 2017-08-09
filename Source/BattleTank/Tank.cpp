// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming_Component"));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation) {
    if (!TankAimingComponent) return;

    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel *NewBarrel) {
    TankAimingComponent->SetBarrel(NewBarrel);
    Barrel = NewBarrel;
}

void ATank::SetTurret(UTankTurret *NewTurret) {
    TankAimingComponent->SetTurret(NewTurret);
}

void ATank::Fire() {

    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

    if (!Barrel || !isReloaded) return;

    UE_LOG(LogTemp, Warning, TEXT("isReloaded ? %d"), isReloaded);

    // Spawn a projectile at the socket location of the barrel
    FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator Rotator = Barrel->GetSocketRotation(FName("Projectile"));

    float Time = GetWorld()->GetTimeSeconds();

    auto SpawnedActor = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotator);
    if (!SpawnedActor) return;
    SpawnedActor->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
}

// Called when the game starts or when spawned
void ATank::BeginPlay() { Super::BeginPlay(); }
