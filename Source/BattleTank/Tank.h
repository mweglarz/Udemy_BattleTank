// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
UCLASS()
class BATTLETANK_API ATank : public APawn {
	GENERATED_BODY()

public:
	FTankDelegate OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	float CurrentHealth = StartingHealth;


public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthRatio() const;

protected:

	ATank();

	// Called when the game starts or when spawned
    virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage,
							 struct FDamageEvent const& DamageEvent,
							 AController* EventInstigator,
							 AActor* DamageCauser) override;

};
