// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;

    UPROPERTY(BlueprintReadOnly)
    UTankMovementComponent* TankMovementComponent = nullptr;

private:
    UPROPERTY(EditAnywhere, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint; // Alternative TSubclassOf

    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 6000; // in cm/s

    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTime = 3; // Reload time in seconds

    // Local reference for barrel to spawn projectiles
    UTankBarrel* Barrel = nullptr;

    double LastFireTime = 0;

public:
    // constructor
    ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category=Action)
    void Fire();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

};
