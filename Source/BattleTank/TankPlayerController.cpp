// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController
(const FObjectInitializer &ObjectInitializer): APlayerController(ObjectInitializer) {

    PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController don't possess a tank"));

    } else {
        UE_LOG(LogTemp, Warning, TEXT("Possesed tank name = %s"), *(ControlledTank->GetName()));
    }

    return;
}

void ATankPlayerController::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
    return;
}

ATank *ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

/// Private methods

void ATankPlayerController::AimTowardsCrosshair() {

    if (!GetControlledTank()) return;

    FVector HitLocation; // Out parameter
    if (GetSightRayHitLocation(HitLocation)) {
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));

        // tell controlled tank to aim at this points
    }

    return;
}

// TODO: Get world location of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {
    // get crosshair location
    // return true if it aim at landscape otherwise return false

    HitLocation = FVector(1.f, 1.f, 1.f);

    return true;
}
