// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    UPROPERTY(EditAnywhere, Category=Firing)
    float LaunchSpeed = 6000; // in cm/s

public:
    // constructor
    ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetBarrel(UTankBarrel* NewBarrel);

    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetTurret(UTankTurret* NewTurret);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

};
