// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto ControlledTank = GetControllerTank();

    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController don't possess a tank"));

    } else {
        UE_LOG(LogTemp, Warning, TEXT("Possesed tank name = %s"), *(ControlledTank->GetName()));
    }
}

ATank *ATankPlayerController::GetControllerTank() const {
    return Cast<ATank>(GetPawn());
}
