// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Interfaces/Barrel.h"
#include "Interfaces/Turret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrel(AimDirection);
        MoveTurret(AimDirection);
	}
}

void UTankAimingComponent::Fire() {

	bool bIsFiringStateOK = FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked;
	if (!ensure(Barrel) || !bIsFiringStateOK) return;

	// Spawn a projectile at the socket location of the barrel
	FVector Location = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator Rotator = Barrel->GetSocketRotation(FName("Projectile"));

	auto SpawnedActor = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotator);
	if (!ensure(SpawnedActor)) return;
	SpawnedActor->LaunchProjectile(LaunchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
	AmmoCount--;
}

void UTankAimingComponent::Initialise(UBarrel *BarrelToSet, UTurret *TurretToSet) {
    if (!ensure(BarrelToSet && TurretToSet)) return;
    Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const { return FiringState; }

int32 UTankAimingComponent::GetAmmoCount() const { return AmmoCount; }

// Called when the game starts
void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
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

	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = ToDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	float AngleToRotate = UTankAimingComponent::GetShortestWay(DeltaRotator.Yaw);
	Turret->Rotate(AngleToRotate);
}

bool UTankAimingComponent::isBarrelMoving() const {
	if (!ensure(Barrel)) return false;
	FVector BarrelForward = Barrel->GetForwardVector().GetSafeNormal();
	FVector AimVector = AimDirection.GetSafeNormal();
	return !BarrelForward.Equals(AimVector, 0.01);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	if (AmmoCount <= 0) {
		FiringState = EFiringState::OutOfAmmo;

	} else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime) {
		FiringState = EFiringState::Reloading;

	} else if (isBarrelMoving()) {
		FiringState = EFiringState::Aiming;

	} else {
		FiringState = EFiringState::Locked;
	}
}

float UTankAimingComponent::GetShortestWay(float Angle) {
	float Sign = Angle < 0 ? -1.f : 1.f;
	Angle = FMath::Abs<float>(Angle);

	return Sign * (Angle > 180.f ? -(360.f - Angle) : Angle);
}
