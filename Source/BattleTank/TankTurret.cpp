// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed) {

    // TODO implement
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto RotateChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float NewRotation = RelativeRotation.Yaw + RotateChange;

    SetRelativeRotation(FRotator(0, NewRotation, 0));
}
