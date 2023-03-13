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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* Mesh;

};