// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_APGameModeBase.h"
#include "AnnihilationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API AAnnihilationGameMode : public AProject_APGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	void EndGame(bool bIsPlayerWinner);
	
};
