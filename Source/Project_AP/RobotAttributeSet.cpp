// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Project_APGameInstance.h"
#include "PlayerHUD.h"
#include "RobotAttributeSet.h"

void URobotAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UPlayerHUD *HUD = Cast<UProject_APGameInstance>(GetWorld()->GetGameInstance())->GetInGameWidget()->GetPlayerHUD();		
		HUD->HealthSetPercent( GetHealth() / GetMaxHealth());

	}

	if (Data.EvaluatedData.Attribute == GetUltimateManaAttribute())
	{
		SetUltimateMana(FMath::Clamp(GetUltimateMana(), 0.f, GetUltimateManaMax()));
		UPlayerHUD* HUD = Cast<UProject_APGameInstance>(GetWorld()->GetGameInstance())->GetInGameWidget()->GetPlayerHUD();
		HUD->UltimateSetPercent(GetUltimateMana() / GetUltimateManaMax());
	}

	if (Data.EvaluatedData.Attribute == GetAutoManaAttribute())
	{
		SetAutoMana(FMath::Clamp(GetAutoMana(), 0.f, GetAutoManaMax()));
		UPlayerHUD* HUD = Cast<UProject_APGameInstance>(GetWorld()->GetGameInstance())->GetInGameWidget()->GetPlayerHUD();
		HUD->AutoSetPercent(GetAutoMana() / GetAutoManaMax());
	}

}


