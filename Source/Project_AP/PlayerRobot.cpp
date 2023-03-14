// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRobot.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RobotMovementComponent.h"

APlayerRobot::APlayerRobot()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MovementComponent = CreateDefaultSubobject<URobotMovementComponent>(TEXT("MovementComponent"));

	RootComponent = Mesh;
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

}

void APlayerRobot::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerRobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerRobot::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerRobot::MoveRight);
}

void APlayerRobot::MoveForward(float Value)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SetMoveForward(Value);
}
void APlayerRobot::MoveRight(float Value)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SetMoveRight(Value);
}



