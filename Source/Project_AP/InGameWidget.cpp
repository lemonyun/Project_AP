// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"
#include "Input/Events.h"
#include "InGameButton.h"
#include "Components/CanvasPanelSlot.h"

bool UInGameWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success)
        return false;

    if (MoveButton == nullptr) return false;

    if (AttackButton == nullptr) return false;

    if (UltimateButton == nullptr) return false;
  
    AttackButton->AddButtonToInActiveList(UltimateButton);
    UltimateButton->AddButtonToInActiveList(AttackButton);

    return true;
    
}