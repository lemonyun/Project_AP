// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotMovementComponent.h"

// Sets default values for this component's properties
URobotMovementComponent::URobotMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URobotMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URobotMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	Velocity = FVector(MoveForward, MoveRight, 0) * MoveSpeed;
	
	UpdateLocationFromVelocity(DeltaTime);
}

void URobotMovementComponent::SetMoveForward(float Value)
{
	MoveForward = Value;
}

void URobotMovementComponent::SetMoveRight(float Value)
{
	MoveRight = Value;
}

void URobotMovementComponent::SetAttackForward(float Value)
{
	AttackForward = Value;
}

void URobotMovementComponent::SetAttackRight(float Value)
{
	AttackRight = Value;
}

void URobotMovementComponent::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;
	FHitResult Hit;
	GetOwner()->AddActorWorldOffset(Translation, true, &Hit);
	if (Hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}
