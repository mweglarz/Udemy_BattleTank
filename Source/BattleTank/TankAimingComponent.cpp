// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
    if (!ensure(Barrel)) return;

    FVector OutLaunchVelocity;
    auto BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));

    bool bCanHit = UGameplayStatics::SuggestProjectileVelocity(
                       this,
                       OutLaunchVelocity,
                       BarrelLocation,
                       HitLocation,
                       LaunchSpeed,
                       false,
                       0.f,
                       0.f,
                       ESuggestProjVelocityTraceOption::DoNotTrace);

    if (bCanHit) {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrel(AimDirection);
        MoveTurret(AimDirection);
    }
}

void UTankAimingComponent::Fire() {
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

    if (!ensure(Barrel) || !isReloaded) return;

    // Spawn a projectile at the socket location of the barrel
    FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator Rotator = Barrel->GetSocketRotation(FName("Projectile"));

    auto SpawnedActor = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotator);
    if (!ensure(SpawnedActor)) return;
    SpawnedActor->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {
    if (!ensure(BarrelToSet && TurretToSet)) return;
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();
}

/** ***** PRIVATE ***** */

void UTankAimingComponent::MoveBarrel(FVector ToDirection) {
    if (!ensure(Barrel)) return;

    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = ToDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector ToDirection) {
    if (!ensure(Turret)) return;

    auto TurretRotator = Turret->GetForwardVector().Rotation();
    auto AimAsRotator = ToDirection.Rotation();
    auto DeltaRotator = AimAsRotator - TurretRotator;

    Turret->Rotate(DeltaRotator.Yaw);
}
