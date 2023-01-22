// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if (AIBehavior && playerPawn) {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), playerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // if (!playerPawn) return;
    

    // if (LineOfSightTo(playerPawn)) {
    //     SetFocus(playerPawn);
    //     MoveToActor(playerPawn, acceptanceRadius);
    // }
    // else {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }
}
