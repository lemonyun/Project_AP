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

	// ��ġ ���� ���� ũ��
	UPROPERTY(EditAnywhere)
	FVector2D InteractionSize = FVector2D(800, 800);

protected:
	virtual bool Initialize() override;

private:
	void ChangingTouchSetting();

	// ��ġ ���� ����
	UPROPERTY(meta = (BindWidget))
	class UImage* TouchRange;
	
	// ū ��
	UPROPERTY(meta = (BindWidget))
	class UImage* JoyStickBackGround;

	// ���� ��
	UPROPERTY(meta = (BindWidget))
	class UImage* JoyStickThumb;

	// �ش� ��ư�� Pushed�϶� ��Ȱ��ȭ ��ų �ٸ� ��ư�� (��ġ ���� ������ �����ִ� ��쿡 ��Ȱ��ȭ ���־�� ��)
	UPROPERTY()
	TArray<TObjectPtr<UInGameButton>> ButtonToInActive;

	// ��ġ ���� ���������� Joystick ������
	UPROPERTY(EditAnywhere)
	FVector2D JoystickOffset;

	// Thumb ���� ����
	UPROPERTY(EditAnywhere)
	float Radius = 120;

	// ū ���� �����̴� ��ư�ΰ�? (MoveButton)
	UPROPERTY(EditAnywhere)
	bool bIsBackgroundMove = false;

	// ��ġ ������ �ٲ�� ��ư�ΰ�? (UltimateButton)
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
