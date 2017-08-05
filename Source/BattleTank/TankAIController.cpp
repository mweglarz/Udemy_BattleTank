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

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto PlayerTank = GetPlayerTank();
    auto AITank = GetControlledTank();
    if (PlayerTank && AITank) {
        auto TankLocation = PlayerTank->GetActorLocation();
        AITank->AimAt(TankLocation);
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
