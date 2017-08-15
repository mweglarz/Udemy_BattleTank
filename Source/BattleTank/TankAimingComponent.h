// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState: uint8 {
    Locked,
    Aiming,
    Reloading
};


class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Setup")
    EFiringState FiringState = EFiringState::Aiming;

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

public:	
    UTankAimingComponent();

    UFUNCTION(BlueprintCallable, Category = "Action")
    void AimAt(FVector HitLocation, float LaunchSpeed);

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    void MoveBarrel(FVector ToDirection);
    void MoveTurret(FVector ToDirection);

};
