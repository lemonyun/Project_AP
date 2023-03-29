// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameButton.h"
#include "Components/Image.h"
#include "Layout/Geometry.h"
#include "Input/Reply.h"
#include "Styling/SlateBrush.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"

bool UInGameButton::Initialize()
{
    SquaredRadius = FMath::Square(Radius);

    bool Success = Super::Initialize();
    if (!Success)
        return false;

    if (TouchRange == nullptr) return false;
    if (JoyStickBackGround == nullptr) return false;
    if (JoyStickThumb == nullptr) return false;

    JoyStickThumb->SetRenderTranslation(JoystickOffset);
    JoyStickBackGround->SetRenderTranslation(JoystickOffset);

    Cast<UCanvasPanelSlot>(TouchRange->Slot)->SetSize(InteractionSize);
    

    return true;

}

void UInGameButton::ChangingTouchSetting()
{

}

void UInGameButton::AddButtonToInActiveList(TObjectPtr<UInGameButton> Ptr)
{
    ButtonToInActive.Add(Ptr);
}

FReply UInGameButton::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
    Super::OnTouchStarted(InGeometry, InTouchEvent);

    
    for (TObjectPtr<UInGameButton> ptr : ButtonToInActive)
    {
        ptr->SetVisibility(ESlateVisibility::HitTestInvisible);
    }


    LocalCenter = InGeometry.GetLocalSize() / 2;

    FVector2D LocalWidgetMousePos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, InTouchEvent.GetScreenSpacePosition());

    //background와 thumb 이동
    JoyStickThumb->SetRenderTranslation(LocalWidgetMousePos - LocalCenter);
    JoyStickBackGround->SetRenderTranslation(LocalWidgetMousePos - LocalCenter);

    NextCenter = LocalWidgetMousePos;

    if (bIsRangeChangeButton)
    {
        // OnTouchStartChangeDelegate.ExecuteIfBound();
        Cast<UCanvasPanelSlot>(TouchRange->Slot)->SetSize(ChangingSize);
    }

    bIsPushed = true;


    return FReply::Handled();
}

FReply UInGameButton::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
    if (bIsPushed == false)
        return FReply::Handled();

    Super::OnTouchMoved(InGeometry, InTouchEvent);

    FVector2D LocalWidgetMousePos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, InTouchEvent.GetScreenSpacePosition());
    LocalCenter = InGeometry.GetLocalSize() / 2;

    FVector2D Offset = LocalWidgetMousePos - NextCenter;

    PlayerInput = Offset.GetSafeNormal() * FMath::Clamp(Offset.Size() / Radius, 0, 1);

    // Touch Point가 BackGround를 벗어나는 경우

    if (Offset.SizeSquared() > SquaredRadius)
    {
        // BackGround UI가 같이 움직이도록 하는 버튼의 경우
        if (bIsBackgroundMove)
        {
            NextCenter = NextCenter + Offset - Offset.GetSafeNormal() * FMath::Sqrt(SquaredRadius);

            JoyStickBackGround->SetRenderTranslation(NextCenter - LocalCenter);
            JoyStickThumb->SetRenderTranslation(LocalWidgetMousePos - LocalCenter);
        }
        else
        {

            JoyStickThumb->SetRenderTranslation(NextCenter - LocalCenter + Offset.GetSafeNormal() * FMath::Sqrt(SquaredRadius));
        }
        
    }
    else
    {
        JoyStickThumb->SetRenderTranslation(LocalWidgetMousePos - LocalCenter);
    }
    // Thumb 이동



    return FReply::Handled();
}

FReply UInGameButton::NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent)
{
    Super::OnTouchEnded(InGeometry, InGestureEvent);

    if (bIsPushed == false)
        return FReply::Handled();

    OnTouchEndDelegate.ExecuteIfBound();

    PlayerInput = FVector2D::Zero();

    JoyStickThumb->SetRenderTranslation(JoystickOffset);
    JoyStickBackGround->SetRenderTranslation(JoystickOffset);

    bIsPushed = false;

    for (TObjectPtr<UInGameButton> ptr : ButtonToInActive)
    {
        ptr->SetVisibility(ESlateVisibility::Visible);
    }


    if (bIsRangeChangeButton)
    {
        Cast<UCanvasPanelSlot>(TouchRange->Slot)->SetSize(InteractionSize);
    }


    return FReply::Handled();
}

