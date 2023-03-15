// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerRobot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API APlayerRobot : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerRobot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class URobotMovementComponent* MovementComponent;

	UStaticMeshComponent* GetMeshComponent();
	UStaticMeshComponent* GetWeaponMeshComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	// void Move(FVector Value);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* Capsule;

};
