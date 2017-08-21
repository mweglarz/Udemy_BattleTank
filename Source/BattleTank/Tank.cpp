// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::GetHealthRatio() const {
	float ClampedHealth = FMath::Clamp<float>(CurrentHealth, 0.f, StartingHealth);
	return ClampedHealth / StartingHealth * 100;
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();
}

float ATank::TakeDamage(float Damage, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser) {
	CurrentHealth -= Damage;

	if (CurrentHealth < 0) {
		OnDeath.Broadcast();
	}

	return Damage;
}
