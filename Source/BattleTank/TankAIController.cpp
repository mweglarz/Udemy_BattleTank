// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    auto PlayerTank = GetPlayerTank();
    auto AITank = GetControlledTank();
    if (PlayerTank && AITank) {
        auto TankLocation = PlayerTank->GetActorLocation();
        AITank->AimAt(TankLocation);
        AITank->Fire();

        MoveToActor(PlayerTank, AcceptanceRadius);
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
