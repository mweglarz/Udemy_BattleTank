// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    PrimaryActorTick.bCanEverTick = true;
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    auto PlayerTank = GetPlayerTank();

	if (ensure(PlayerTank && AimingComponent)) {
        auto TankLocation = PlayerTank->GetActorLocation();
		AimingComponent->AimAt(TankLocation);

		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}

        MoveToActor(PlayerTank, AcceptanceRadius);
    }
}

APawn* ATankAIController::GetPlayerTank() const {

    auto PlayerController = GetWorld()->GetFirstPlayerController();

    if (!ensure(PlayerController)) return nullptr;
	return PlayerController->GetPawn();
}

void ATankAIController::SetPawn(APawn *InPawn) {
	Super::SetPawn(InPawn);
	if (!InPawn) return;

	ATank* PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) return;

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}

void ATankAIController::OnTankDeath() {
	APawn* Tank = GetPawn();
	if (!Tank) return;
	Tank->DetachFromControllerPendingDestroy();
}
