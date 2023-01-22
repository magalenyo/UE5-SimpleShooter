// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(
		muzzleFlash,
		mesh,
		TEXT("MuzzleFlashSocket")
	);

	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (!ownerPawn) return;
	AController* ownerController = ownerPawn->GetController();
	if (!ownerController) return;

	FVector location;
	FRotator rotation;
	ownerController->GetPlayerViewPoint(location, rotation);

	FVector end = location + rotation.Vector() * maxRange;

	FHitResult hit;
	bool success = GetWorld()->LineTraceSingleByChannel(
		hit,
		location,
		end,
		ECollisionChannel::ECC_GameTraceChannel1
	);

	if (success) {
		FVector shotDirection = -rotation.Vector();		// where it's being shot from
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			impactEffect,
			hit.Location,
			shotDirection.Rotation()
		);

		AActor* hitActor = hit.GetActor();
		if (hitActor) {
			FPointDamageEvent damageEvent(
				damage,
				hit,
				shotDirection,
				nullptr
			);
			hitActor->TakeDamage(damage, damageEvent, ownerController, this);
		}
	}
	
}

