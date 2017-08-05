// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called every frame
void UTankAimingComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {

    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
    if (!Barrel) return;

    auto TankName = GetOwner()->GetName();

    FVector OutLaunchVelocity;
    auto BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));

    // TODO: calculate outLaunchVelocity
    bool bCanHit = UGameplayStatics::SuggestProjectileVelocity(
                this,
                OutLaunchVelocity,
                BarrelLocation,
                HitLocation,
                LaunchSpeed);


    if (bCanHit) {
        FString CanHitLog = bCanHit ? "true" : "false";

        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrel(AimDirection);

        UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"),
               *TankName,
               *AimDirection.ToString());
    }
    //    UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"),
//           *TankName,
//           *HitLocation.ToString(),
//           *BarrelLocation.ToString());
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent *BarrelToSet) {
    Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();
}

void UTankAimingComponent::MoveBarrel(FVector ToDirection) {

    // TODO: Move the barrel
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = ToDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
}






