// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    UPROPERTY(EditAnywhere, Category=Firing)
    float LaunchSpeed = 50000; // in cm/s

public:
    // constructor
    ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetBarrel(UStaticMeshComponent* NewBarrel);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

};
