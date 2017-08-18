// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxDrivingForce = 40000000;

private:
	float CurrentThrottle = 0.f;

public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);

protected:
	UTankTrack();

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			   UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
			   const FHitResult& Hit);

	void ApplyDriftCorrectionForce();

	void DriveTrack();
};
