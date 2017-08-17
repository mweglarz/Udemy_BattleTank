// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle) {
    // TODO: clamp actual throttle value so player can't over drive

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    if (!ensure(TankRoot)) return;

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!ensure(TankRoot)) return;

	FVector Velocity = GetComponentVelocity();
	FVector RightVector = GetRightVector(); // unit vector

	float SlippageSpeed = FVector::DotProduct(Velocity, RightVector);

	// half the force because of 2 tracks
	FVector DriftCorrectionForce = -0.5 * (SlippageSpeed / DeltaTime * RightVector) * TankRoot->GetMass();

	TankRoot->AddForce(DriftCorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit) {

	UE_LOG(LogTemp, Warning, TEXT("hit ground"));
}


