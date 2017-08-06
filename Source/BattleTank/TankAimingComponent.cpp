// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
    if (!Barrel) return;

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

void UTankAimingComponent::SetBarrel(UTankBarrel *NewBarrel) {
    if (!NewBarrel) return;
    Barrel = NewBarrel;
}

void UTankAimingComponent::SetTurret(UTankTurret *NewTurret) {
    if (!NewTurret) return;
    Turret = NewTurret;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();
}

void UTankAimingComponent::MoveBarrel(FVector ToDirection) {

    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = ToDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector ToDirection) {

    auto TurretRotator = Turret->GetForwardVector().Rotation();
    auto AimAsRotator = ToDirection.Rotation();
    auto DeltaRotator = AimAsRotator - TurretRotator;

    Turret->Rotate(DeltaRotator.Yaw);
}
