// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameButton.h"
#include "Components/Image.h"
#include "Layout/Geometry.h"
#include "Input/Reply.h"
#include "Styling/SlateBrush.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/SlateBlueprintLibrary.h"

bool UInGameButton::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success)
        return false;

    if (TouchRange == nullptr) return false;
    if (JoyStickBackGround == nullptr) return false;
    if (JoyStickThumb == nullptr) return false;

    return true;

}

FReply UInGameButton::NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
    Super::OnTouchStarted(InGeometry, InTouchEvent);

    FVector2D LocalWidgetMousePos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, InTouchEvent.GetScreenSpacePosition());
    
    LocalCenter = InGeometry.GetLocalSize() / 2;

    //background와 thumb 이동
    JoyStickThumb->SetRenderTranslation(LocalWidgetMousePos - LocalCenter);
    JoyStickBackGround->SetRenderTranslation(LocalWidgetMousePos - LocalCenter);

    NextCenter = LocalWidgetMousePos;

    UE_LOG(LogTemp, Warning, TEXT("LocalWidgetMousePos %f %f"), LocalWidgetMousePos.X, LocalWidgetMousePos.Y);


    return FReply::Handled();
}

FReply UInGameButton::NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InTouchEvent)
{
    Super::OnTouchMoved(InGeometry, InTouchEvent);

    FVector2D LocalWidgetMousePos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, InTouchEvent.GetScreenSpacePosition());
    LocalCenter = InGeometry.GetLocalSize() / 2;

    FVector2D Offset = LocalWidgetMousePos - NextCenter;

    PlayerInput = Offset.GetSafeNormal();

   

    UE_LOG(LogTemp, Warning, TEXT("InputVector %f %f"), PlayerInput.X, PlayerInput.Y);

    
    // Touch Point가 BackGround를 벗어나는 경우

    UE_LOG(LogTemp, Warning, TEXT("size Square %f"), Offset.SizeSquared());
    if (Offset.SizeSquared() > SquaredRadius)
    {
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


    JoyStickThumb->SetRenderTranslation(FVector2D::Zero());
    JoyStickBackGround->SetRenderTranslation(FVector2D::Zero());

    PlayerInput = FVector2D::Zero();

    return FReply::Handled();
}

