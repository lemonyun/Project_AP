// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "ProjectAPGameInstance.h"
#include "PlayerHUD.h"
#include "RobotPlayerController.h"

#include "AIRobot.h"
#include "RobotAIController.h"
#include "PlayerRobot.h"
#include "FloatingWidget.h"
#include "AnnihilationGameMode.h"

void URobotAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	UPlayerHUD* PlayerHUD = nullptr;
	UFloatingWidget* AIHUD = nullptr;



	if (APlayerRobot* Robot = Cast<APlayerRobot>(GetOwningActor()))
	{
		if (ARobotPlayerController* RobotController = Cast<ARobotPlayerController>(Robot->GetController()))
		{
			PlayerHUD = RobotController->GetInGameWidget()->GetPlayerHUD();
		}
	}
	else if (AAIRobot* AIRobot = Cast<AAIRobot>(GetOwningActor()))
	{
		AIHUD = AIRobot->GetFloatingBarWidget();
	}


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		if (PlayerHUD != nullptr)
		{
			PlayerHUD->HealthSetPercent(GetHealth() / GetMaxHealth());
		}
		
		if (AIHUD != nullptr)
		{
			AIHUD->HealthSetPercent(GetHealth() / GetMaxHealth());
		}

		if (GetHealth() <= 0)
		{
			AAnnihilationGameMode* GameMode = GetWorld()->GetAuthGameMode<AAnnihilationGameMode>();
			APawn* Pawn = Cast<APawn>(GetOwningActor());
			if (GameMode != nullptr)
			{
				GameMode->PawnKilled(Pawn);
			}

			// Pawn->DetachFromControllerPendingDestroy();
			Pawn->Destroy();
		}
		
	}

	if (Data.EvaluatedData.Attribute == GetUltimateManaAttribute())
	{
		SetUltimateMana(FMath::Clamp(GetUltimateMana(), 0.f, GetUltimateManaMax()));
		if (PlayerHUD != nullptr)
		{
			PlayerHUD->UltimateSetPercent(GetUltimateMana() / GetUltimateManaMax());
		}

	}

	if (Data.EvaluatedData.Attribute == GetAutoManaAttribute())
	{
		SetAutoMana(FMath::Clamp(GetAutoMana(), 0.f, GetAutoManaMax()));
		if (PlayerHUD != nullptr)
		{
			PlayerHUD->AutoSetPercent(GetAutoMana() / GetAutoManaMax());
		}


	}

}



