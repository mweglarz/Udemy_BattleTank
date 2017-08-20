// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AProjectile::AProjectile() {
    // Set this actor to call Tick() every frame.  You can turn this off to
    // improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetupDefaultComponents();
}

void AProjectile::LaunchProjectile(float Speed) {

    float Time = GetWorld()->GetTimeSeconds();

    MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    MovementComponent->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();

	SetupOnHitDelegate();
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit) {

	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle OutTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(OutTimerHandle, this, &AProjectile::LifetimeTimerExpired, DestroyDelay);
}

void AProjectile::LifetimeTimerExpired() {
	Destroy();
}

void AProjectile::SetupDefaultComponents() {

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile_Movement"));
	MovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision_Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch_Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact_Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion_Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::SetupOnHitDelegate() {
	if (!ensure(CollisionMesh)) return;
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}
