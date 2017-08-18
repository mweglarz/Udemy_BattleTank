// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Engine/World.h"


void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2.f, 2.f);
}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit) {

	ApplyDriftCorrectionForce();
	DriveTrack();
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplyDriftCorrectionForce() {

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) return;

	FVector Velocity = GetComponentVelocity();
	FVector RightVector = GetRightVector(); // unit vector

	float SlippageSpeed = FVector::DotProduct(Velocity, RightVector);
	float DeltaTime = GetWorld()->DeltaTimeSeconds;

	// half the force because of 2 tracks
	FVector DriftCorrectionForce = -0.5 * (SlippageSpeed / DeltaTime * RightVector) * TankRoot->GetMass();

	TankRoot->AddForce(DriftCorrectionForce);
}

void UTankTrack::DriveTrack() {

	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	if (!ensure(TankRoot)) return;

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


