// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UInGameButton* GetMoveButton() { return MoveButton; }
	class UInGameButton* GetAttackButton() { return AttackButton; }

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UInGameButton* MoveButton;

	UPROPERTY(meta = (BindWidget))
	class UInGameButton* AttackButton;

	//UPROPERTY(meta = (BindWidget))
	//class UW_InGameButton* AttackButton;	

	

};
