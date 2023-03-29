// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AIRobot.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AAIRobot* AIRobot = Cast<AAIRobot>(OwnerComp.GetAIOwner()->GetPawn());
    if (AIRobot == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    
    UObject* PlayerObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Player"));

    if (APlayerRobot* PlayerRobot = Cast<APlayerRobot>(PlayerObject))
    {
        AIRobot->SetPlayerRobot(PlayerRobot);

        // 플레이어를 향해 일반 공격
        AIRobot->ActivateAbility(0);

    }


    

    return EBTNodeResult::Succeeded;
}
