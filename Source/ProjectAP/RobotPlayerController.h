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
class PROJECTAP_API ARobotPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	ARobotPlayerController();

	UFUNCTION(BlueprintCallable)
	void LoadInGameWidget();

	UInGameWidget* GetInGameWidget() { return InGameWidget; }

	void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner);

private:

	TSubclassOf<UInGameWidget> WidgetClass;
	class UInGameWidget* InGameWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	FTimerHandle RestartTimer;

};
