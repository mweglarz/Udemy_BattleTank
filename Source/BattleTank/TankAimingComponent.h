// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

public:	
    UTankAimingComponent();

    void AimAt(FVector HitLocation, float LaunchSpeed);
    void SetBarrel(UTankBarrel* NewBarrel);
    void SetTurret(UTankTurret* NewTurret);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    void MoveBarrel(FVector ToDirection);
    void MoveTurret(FVector ToDirection);

};
