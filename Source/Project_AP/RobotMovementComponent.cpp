// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "PlayerRobot.h"
#include "Kismet/GameplayStatics.h"
#include "Project_APGameInstance.h"
#include "InGameWidget.h"
#include "InGameButton.h"

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
	
	InGameWidget = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget();

	Mesh = Cast<APlayerRobot>(GetOwner())->GetMeshComponent();
	WeaponMesh = Cast<APlayerRobot>(GetOwner())->GetWeaponMeshComponent();
}


// Called every frame
void URobotMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector2D PlayerMoveInput = InGameWidget->GetMoveButton()->GetPlayerInput();
	MoveForward = -PlayerMoveInput.Y;
	MoveRight = PlayerMoveInput.X;

	FVector NewMoveVector = FVector(MoveForward, MoveRight, 0);

	Velocity = NewMoveVector * MoveSpeed;
	
	UpdateLocationFromVelocity(DeltaTime);

	if (Velocity != FVector::ZeroVector) 
	{
		UpdateRotation(DeltaTime);
	}
	
	// Weapon Mesh Rotation 업데이트

	FVector2D PlayerAttackInput = InGameWidget->GetAttackButton()->GetPlayerInput();


	AttackForward = -PlayerAttackInput.Y;
	AttackRight = PlayerAttackInput.X;

	WeaponRotationVector = FVector(AttackForward, AttackRight, 0);

	if (WeaponRotationVector != FVector::ZeroVector)
	{
		UpdateWeaponRotation(DeltaTime);
	}


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

void URobotMovementComponent::UpdateRotation(float DeltaTime)
{
	// float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime;

	FRotator CurrentRotator = Mesh->GetComponentRotation();
	
	FRotator TargetRotator = Velocity.Rotation();

	FRotator SmoothRotator = FMath::RInterpTo(CurrentRotator, TargetRotator, DeltaTime, 3.0f);
	// FRotator SmoothRotator = TargetRotator;

	Mesh->SetRelativeRotation(SmoothRotator);
	
}

void URobotMovementComponent::UpdateWeaponRotation(float DeltaTime)
{

	WeaponMesh->SetWorldRotation(WeaponRotationVector.Rotation());
	
}
