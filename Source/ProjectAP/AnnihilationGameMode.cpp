// Fill out your copyright notice in the Description page of Project Settings.


#include "AnnihilationGameMode.h"
#include "RobotAIController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AAnnihilationGameMode::PawnKilled(APawn* PawnKilled)
{

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (ARobotAIController* AIRobotController : TActorRange<ARobotAIController>(GetWorld()))
    {
        if (!AIRobotController->IsDead())
        {
            return;
        }

    }

    EndGame(true);
}

void AAnnihilationGameMode::EndGame(bool bIsPlayerWinner)
{
    for (APlayerController* Controller : TActorRange<APlayerController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
