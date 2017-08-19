// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Barrel.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UBarrel {
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 5;
	
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees = 30;

    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegress = 0;

};
