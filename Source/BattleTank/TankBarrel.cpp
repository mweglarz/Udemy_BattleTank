// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed) {

    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float NewElevation = RelativeRotation.Pitch + ElevationChange;
    NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegress, MaxElevationDegrees);

    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
