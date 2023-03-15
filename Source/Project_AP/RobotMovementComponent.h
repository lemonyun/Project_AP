// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RobotMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_AP_API URobotMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URobotMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMoveForward(float Value);
	void SetMoveRight(float Value);

	void SetAttackForward(float Value);
	void SetAttackRight(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	class UStaticMeshComponent* Mesh;
	class UStaticMeshComponent* WeaponMesh;

	void UpdateLocationFromVelocity(float DeltaTime);
	
	void UpdateRotation(float DeltaTime);

	float MoveForward;
	float MoveRight;

	float AttackForward;
	float AttackRight;

	FVector Velocity;
	FVector WeaponRotationVector;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.f;

	class UInGameWidget* InGameWidget;

	void UpdateWeaponRotation(float DeltaTime);
};
