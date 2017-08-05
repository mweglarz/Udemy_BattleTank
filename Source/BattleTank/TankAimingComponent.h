// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
    UStaticMeshComponent* Barrel = nullptr;

public:	
    UTankAimingComponent();

    // Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void AimAt(FVector HitLocation, float LaunchSpeed);

    void SetBarrel(UStaticMeshComponent* BarrelToSet);
    // TODO: add SetTuret

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    void MoveBarrel(FVector ToDirection);

};
