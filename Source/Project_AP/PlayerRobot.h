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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* WeaponComponent;

	class UProjectileTrajectoryComponent* GetProjectileProjectileComponent() { return ProjectileTrajectory; }
	class UWeaponComponent* GetWeaponComponent() { return WeaponComponent; }
	class UStaticMeshComponent* GetMeshComponent() { return BaseMesh; }
	class UStaticMeshComponent* GetWeaponMeshComponent() { return WeaponMesh; }
	class USceneComponent* GetProjectileStartPoint() { return ProjectileStartPoint; }


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

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileTrajectoryComponent* ProjectileTrajectory;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileStartPoint;
};
