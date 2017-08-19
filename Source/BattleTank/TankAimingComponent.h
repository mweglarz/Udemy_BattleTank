// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState: uint8 {
    Locked,
    Aiming,
	Reloading,
	OutOfAmmo
};


class UTurret;
class UBarrel;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 10;

private:
	UBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 6000; // [cm/s]

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3; // Reload time in seconds

	double LastFireTime = 0;
	FVector AimDirection = FVector(0);

public:	
    UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Firing")
    void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Firing")
	void Fire();

    UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UBarrel* BarrelToSet, UTurret* TurretToSet);

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoCount() const;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    void MoveBarrel(FVector ToDirection);
    void MoveTurret(FVector ToDirection);
	bool isBarrelMoving() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	static float GetShortestWay(float Angle);
};
