// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();

    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("TankAIController have no tank to control!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("AIControlled tank = %s"), *(ControlledTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() {
    return Cast<ATank>(GetPawn());
}
