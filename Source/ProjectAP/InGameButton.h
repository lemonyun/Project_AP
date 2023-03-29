// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameButton.generated.h"

DECLARE_DELEGATE (OnTouchEnd);

UCLASS()
class PROJECTAP_API UInGameButton : public UUserWidget
{

	GENERATED_BODY()

public:
	FVector2D GetPlayerInput() { return PlayerInput; }

	OnTouchEnd OnTouchEndDelegate;


	void AddButtonToInActiveList(TObjectPtr<UInGameButton> Ptr);

	UPROPERTY(EditAnywhere)
	FVector2D ChangingSize = FVector2D(800, 800);

	// 터치 가능 영역 크기
	UPROPERTY(EditAnywhere)
	FVector2D InteractionSize = FVector2D(800, 800);

protected:
	virtual bool Initialize() override;

private:
	void ChangingTouchSetting();

	// 터치 가능 영역
	UPROPERTY(meta = (BindWidget))
	class UImage* TouchRange;
	
	// 큰 원
	UPROPERTY(meta = (BindWidget))
	class UImage* JoyStickBackGround;

	// 작은 원
	UPROPERTY(meta = (BindWidget))
	class UImage* JoyStickThumb;

	// 해당 버튼이 Pushed일때 비활성화 시킬 다른 버튼들 (터치 가능 영역이 겹쳐있는 경우에 비활성화 해주어야 함)
	UPROPERTY()
	TArray<TObjectPtr<UInGameButton>> ButtonToInActive;

	// 터치 가능 영역에서의 Joystick 오프셋
	UPROPERTY(EditAnywhere)
	FVector2D JoystickOffset;

	// Thumb 가동 범위
	UPROPERTY(EditAnywhere)
	float Radius = 120;

	// 큰 원이 움직이는 버튼인가? (MoveButton)
	UPROPERTY(EditAnywhere)
	bool bIsBackgroundMove = false;

	// 터치 범위가 바뀌는 버튼인가? (UltimateButton)
	UPROPERTY(EditAnywhere)
	bool bIsRangeChangeButton;

	FReply NativeOnTouchStarted(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	FReply NativeOnTouchMoved(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	FReply NativeOnTouchEnded(const FGeometry& InGeometry, const FPointerEvent& InGestureEvent) override;
	
	float SquaredRadius = 14400;

	bool bIsPushed = false;

	FVector2D NextCenter;

	FVector2D PlayerInput;

	FVector2D LocalCenter;


};
