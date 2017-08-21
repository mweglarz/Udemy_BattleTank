// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.f;

	UTankAimingComponent* AimingComponent;

public:
    ATankPlayerController(const FObjectInitializer &ObjectInitializer);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds);

protected:

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:

    // Move tank barrel so it shots where crosshair intersects the world/landscape
    void AimTowardsCrosshair();

    // Return HitLocation coordinates as OUT parameter and bool if we are hiting
    // landscape or not
    bool GetSightRayHitLocation(FVector &HitLocation) const;

    // Get crosshair look direction in world
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    // GetHitLocation based on max range and look direction
    bool GetLookVectorHitLocation(FVector& HitLocation, const FVector LookDirection) const;

	virtual void SetPawn(APawn *InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};
