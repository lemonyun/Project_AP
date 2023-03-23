// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "RobotAttributeSet.h"

void URobotAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}



}


