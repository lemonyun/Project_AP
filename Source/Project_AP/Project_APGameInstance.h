// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InGameWidget.h"
#include "Project_APGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API UProject_APGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UProject_APGameInstance();

	UFUNCTION(BlueprintCallable)
	void LoadInGameWidget();


private:
	
	TSubclassOf<UInGameWidget> WidgetClass;
	class UInGameWidget* InGameWidget;

};
