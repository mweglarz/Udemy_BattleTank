// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()

public:
    ATankPlayerController(const FObjectInitializer &ObjectInitializer);
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds);
    ATank* GetControlledTank() const;

private:

    // Move tank barrel so it shots where crosshair intersects the world/landscape
    void AimTowardsCrosshair();
    // Return HitLocation coordinates as OUT parameter and bool if we are hiting
    // landscape or not
    bool GetSightRayHitLocation(FVector &HitLocation) const;
};
