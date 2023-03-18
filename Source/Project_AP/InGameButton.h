// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameButton.generated.h"

DECLARE_DELEGATE (OnTouchEnd);

UCLASS()
class PROJECT_AP_API UInGameButton : public UUserWidget
{

	GENERATED_BODY()

public:
	FVector2D GetPlayerInput() { return PlayerInput; }

	OnTouchEnd OnTouchEndDelegate;

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* TouchRange;

	UPROPERTY(meta = (BindWidget))
	class UImage* JoyStickBackGround;

	UPROPERTY(meta = (BindWidget))
	class UImage* JoyStickThumb;

	UPROPERTY(EditAnywhere)
	FVector2D JoystickOffset;

	UPROPERTY(EditAnywhere)
	FVector2D Center;

	UPROPERTY(EditAnywhere)
	FVector2D VisualSize;

	UPROPERTY(EditAnywhere)
	FVector2D ThumbSize;

	UPROPERTY(EditAnywhere)
	FVector2D InteractionSize;

	UPROPERTY(EditAnywhere)
	float Radius = 120;

	UPROPERTY(EditAnywhere)
	bool bIsBackgroundMove = false;

	FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	
	float SquaredRadius = 14400;

	FVector2D NextCenter;

	FVector2D PlayerInput;

	FVector2D LocalCenter;
};
