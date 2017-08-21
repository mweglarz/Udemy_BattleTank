// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController {
	GENERATED_BODY()

protected:
	// How close AI tank can get to player tank
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 8000;
	
private:
	UTankAimingComponent* AimingComponent;

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    APawn* GetPlayerTank() const;
	virtual void SetPawn(APawn *InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};
