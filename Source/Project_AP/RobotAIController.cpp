// Fill out your copyright notice in the Description page of Project Settings.

#include "AIRobot.h"
#include "RobotAIController.h"

bool ARobotAIController::IsDead() const
{
    AAIRobot* AIRobot = Cast<AAIRobot>(GetPawn());

    if (AIRobot != nullptr)
    {
        return AIRobot->IsDead();
    }

    return true;
}