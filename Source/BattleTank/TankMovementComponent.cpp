// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
    if (!AreTracksSet()) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    if (!AreTracksSet()) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet,
                                        UTankTrack *RightTrackToSet) {

    if (!ensure(LeftTrackToSet && RightTrackToSet)) return;
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) {

    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

    auto ForwardRelativeSpeed = FVector::DotProduct(AIForwardIntention, TankForward);
    auto TurnRelativeSpeed = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

    IntendMoveForward(ForwardRelativeSpeed);
    IntendTurnRight(TurnRelativeSpeed);
}

bool UTankMovementComponent::AreTracksSet() { return ensure(LeftTrack && RightTrack); }
