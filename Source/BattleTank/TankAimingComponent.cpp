// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TankBarrel.h"


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
                       LaunchSpeed,
                       false,
                       0.f,
                       0.f,
                       ESuggestProjVelocityTraceOption::DoNotTrace);

    auto Time = GetWorld()->GetTimeSeconds();

    if (bCanHit) {
        FString CanHitLog = bCanHit ? "true" : "false";

        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrel(AimDirection);

        UE_LOG(LogTemp, Warning, TEXT("%f aim solution found"), Time);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("%f no aim solve found"), Time);
    }
}

void UTankAimingComponent::SetBarrel(UTankBarrel *BarrelToSet) {
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

//    UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

    Barrel->Elevate(5); // TODO remove magic number
}






