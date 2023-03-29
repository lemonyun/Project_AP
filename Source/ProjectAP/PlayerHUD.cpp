// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"


bool UPlayerHUD::Initialize()
{
	bool Success = Super::Initialize();
    if (!Success)
        return false;

    if (HealthBar == nullptr) return false;
    if (UltimateBar == nullptr) return false;
    if (AutoBar == nullptr) return false;

    return true;


}
