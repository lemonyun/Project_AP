// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotPlayerController.h"
#include "Blueprint/UserWidget.h"

ARobotPlayerController::ARobotPlayerController()
{
    static ConstructorHelpers::FClassFinder<UInGameWidget> MenuBPClass(TEXT("/Game/Gameplay/Widget/Widgets/W_InGameWidget"));

    if (MenuBPClass.Class == nullptr)
        return;

    WidgetClass = MenuBPClass.Class;
}

void ARobotPlayerController::LoadInGameWidget()
{
    if (WidgetClass == nullptr)
        return;

    InGameWidget = CreateWidget<UInGameWidget>(this, WidgetClass);

    if (InGameWidget == nullptr)
        return;

    InGameWidget->AddToViewport();
}

void ARobotPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    InGameWidget->RemoveFromViewport();
    if (bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}