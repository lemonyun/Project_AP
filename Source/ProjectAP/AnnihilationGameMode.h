// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectAPGameModeBase.h"
#include "AnnihilationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAP_API AAnnihilationGameMode : public AProjectAPGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	void EndGame(bool bIsPlayerWinner);
	
};
