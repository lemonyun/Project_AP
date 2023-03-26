// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGameWidget.h"

#include "RobotPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API ARobotPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	ARobotPlayerController();

	UFUNCTION(BlueprintCallable)
	void LoadInGameWidget();

	UInGameWidget* GetInGameWidget() { return InGameWidget; }

private:

	TSubclassOf<UInGameWidget> WidgetClass;
	class UInGameWidget* InGameWidget;

};