// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RobotAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API ARobotAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	bool IsDead() const;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior; 
};
