// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRobot.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RobotMovementComponent.h"
#include "Components/CapsuleComponent.h"


APlayerRobot::APlayerRobot()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	MovementComponent = CreateDefaultSubobject<URobotMovementComponent>(TEXT("MovementComponent"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	RootComponent = Capsule;
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);
	BaseMesh->SetupAttachment(Capsule);
	WeaponMesh->SetupAttachment(BaseMesh);

}

UStaticMeshComponent* APlayerRobot::GetMeshComponent()
{
	return BaseMesh;
}

UStaticMeshComponent* APlayerRobot::GetWeaponMeshComponent()
{
	return WeaponMesh;
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

	// PlayerInputComponent->BindVectorAxis("Move", this, &APlayerRobot:Move);
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

//void APlayerRobot::Move(FVector Value)
//{
//	MovementComponent->SetMoveForward(Value.X);
//	MovementComponent->SetMoveRight(Value.Y);
//}




