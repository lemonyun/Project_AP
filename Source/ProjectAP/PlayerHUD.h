// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "PlayerHUD.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTAP_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void HealthSetPercent(float Percent) { HealthBar->SetPercent(Percent); }
	void UltimateSetPercent(float Percent) { UltimateBar->SetPercent(Percent); }
	void AutoSetPercent(float Percent) { AutoBar->SetPercent(Percent); }

protected:
	virtual bool Initialize() override;

private:
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* UltimateBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* AutoBar;

	
};
