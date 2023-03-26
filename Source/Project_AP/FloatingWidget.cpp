// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingWidget.h"
#include "Components/ProgressBar.h"

void UFloatingWidget::HealthSetPercent(float HealthPercentage)
{
	HealthBar->SetPercent(HealthPercentage);
}
