// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
    // TODO: prevent for double accelerating
    if (!AreTracksSet()) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    if (!AreTracksSet()) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw) {
    if (!AreTracksSet()) return;
    LeftTrack->SetThrottle(-Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet,
                                        UTankTrack *RightTrackToSet) {

    if (!LeftTrackToSet || !RightTrackToSet) return;
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {
    UE_LOG(LogTemp, Warning, TEXT("%s movevelocity: %s"), *(GetOwner()->GetName()), *MoveVelocity.ToString());
}

bool UTankMovementComponent::AreTracksSet() { return LeftTrack && RightTrack; }
