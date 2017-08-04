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

    auto PlayerTank = GetPlayerTank();
    if (PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("Aiming at player tank %s"), *(PlayerTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {

    auto PlayerController = GetWorld()->GetFirstPlayerController();

    if (!PlayerController) return nullptr;
    return Cast<ATank>(PlayerController->GetPawn());
}
