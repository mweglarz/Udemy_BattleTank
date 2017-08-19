// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20;

public:
	virtual void Rotate(float RelativeSpeed);
	
};
