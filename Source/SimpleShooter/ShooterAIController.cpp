// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    if (!playerPawn) return;
    

    if (LineOfSightTo(playerPawn)) {
        SetFocus(playerPawn);
        MoveToActor(playerPawn, acceptanceRadius);
    }
    else {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}
