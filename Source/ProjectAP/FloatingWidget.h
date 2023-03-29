// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAP_API UFloatingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void HealthSetPercent(float HealthPercentage);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

};
