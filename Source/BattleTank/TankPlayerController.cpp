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
    HitLocation = FVector(0.f);
    UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));

    return;
}

// TODO: Get world location of linetrace through crosshair, return true if landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {

    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY; // OUT parameters
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation,
                                    ViewportSizeY * CrossHairYLocation);
    FVector LookDirection;

    bool bHaveLookDirection = GetLookDirection(ScreenLocation, LookDirection);

    if (bHaveLookDirection) {
        // Line-trace along that look direction, and see what we hit (up to max range)
       return GetLookVectorHitLocation(HitLocation, LookDirection);
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation,
                                             FVector &LookDirection) const {

     // "De-project" the screen position of the crosshair to a world direction
    FVector CameraWorldLocation; // OUT parameter

    return DeprojectScreenPositionToWorld(ScreenLocation.X,
                                          ScreenLocation.Y,
                                          CameraWorldLocation,
                                          LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation,
                                                     const FVector LookDirection) const {

    FHitResult Hit;
    auto Start = PlayerCameraManager->GetCameraLocation();
    auto End = Start + (LookDirection * LineTraceRange);

    bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(Hit,
                             Start,
                             End,
                             ECollisionChannel::ECC_Visibility);

    if (bHitSuccess) {
        HitLocation = Hit.Location;
    }

    return bHitSuccess;
}








