// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UBarrel : public UStaticMeshComponent {
	GENERATED_BODY()
	
protected:
	float MaxDegreesPerSecond = 5;
	float MaxElevationDegrees = 30;
	float MinElevationDegress = 0;

public:
	virtual void Elevate(float RelativeSpeed);
};
