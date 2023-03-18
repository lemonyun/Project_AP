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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	void UpdateLocationFromVelocity(float DeltaTime);
	void UpdateRotation(float DeltaTime);
		
private:
	class UStaticMeshComponent* Mesh;
	
	float MoveForward;
	float MoveRight;

	FVector Velocity;


	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5.f;

	class UInGameButton* MoveButton;


};
