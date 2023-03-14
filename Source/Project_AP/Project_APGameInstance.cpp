// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_APGameInstance.h"
#include "Blueprint/UserWidget.h"

UProject_APGameInstance::UProject_APGameInstance()
{
    static ConstructorHelpers::FClassFinder<UInGameWidget> MenuBPClass(TEXT("/Game/MenuSystem/Widgets/W_InGameWidget"));

    if (MenuBPClass.Class == nullptr)
        return;

    WidgetClass = MenuBPClass.Class;
}

void UProject_APGameInstance::LoadInGameWidget()
{
    if (WidgetClass == nullptr)
        return;

    InGameWidget = CreateWidget<UInGameWidget>(this, WidgetClass);

    if (InGameWidget == nullptr)
        return;

    InGameWidget->AddToViewport();
}
