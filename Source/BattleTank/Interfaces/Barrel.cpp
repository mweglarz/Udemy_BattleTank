// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"
#include "Engine/World.h"

void UBarrel::Elevate(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationDegress, MaxElevationDegrees);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}
