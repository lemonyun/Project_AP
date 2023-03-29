// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotAIController.h"
#include "AIRobot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

bool ARobotAIController::IsDead() const
{
    AAIRobot* AIRobot = Cast<AAIRobot>(GetPawn());

    if (AIRobot != nullptr)
    {
        return AIRobot->IsDead();
    }

    return true;
}

void ARobotAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}