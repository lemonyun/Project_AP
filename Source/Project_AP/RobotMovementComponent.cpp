// Fill out your copyright notice in the Description page of Project Settings.


#include "RobotMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "PlayerRobot.h"
#include "Kismet/GameplayStatics.h"
#include "Project_APGameInstance.h"
#include "InGameWidget.h"
#include "InGameButton.h"
#include "GameFramework/SpringArmComponent.h"

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
	APlayerRobot* Owner = Cast<APlayerRobot>(GetOwner());
	if (Owner != nullptr)
	{
		Mesh = Owner->GetMeshComponent();
		SpringArm = Owner->GetSpringArmComponent();
	}
	

	MoveButton = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget()->GetMoveButton();
	RotateButton = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget()->GetRotateButton();

}


// Called every frame
void URobotMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// Player Move 입력값
	FVector2D PlayerMoveInput = MoveButton->GetPlayerInput();

	// Movement는 Input의 크기에 상관 없이 같은 크기를 가진다.
	FVector2D NormalizedInput = PlayerMoveInput.GetSafeNormal();

	MoveForward = -NormalizedInput.Y;
	MoveRight = NormalizedInput.X;

	FVector NewMoveVector = FVector(MoveForward, MoveRight, 0);
	
	FRotator SpringArmRotator = SpringArm->GetRelativeRotation();
	SpringArmRotator.Pitch = 0;

	NewMoveVector = SpringArmRotator.Quaternion().RotateVector(NewMoveVector);

	Velocity = NewMoveVector * MoveSpeed;
	
	UpdateLocationFromVelocity(DeltaTime);

	if (Velocity != FVector::ZeroVector) 
	{
		UpdateRotation(DeltaTime);
	}

	// Camera Arm 회전
	FVector2D CameraRotationInput = RotateButton->GetPlayerInput();
	
	CameraVelocity = CameraRotationInput.GetSafeNormal().X;

	if (FMath::Abs(CameraVelocity) > KINDA_SMALL_NUMBER)
	{
		UpdateCameraRotation(DeltaTime);
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

void URobotMovementComponent::UpdateCameraRotation(float DeltaTime)
{
	FRotator CurrentRotator = SpringArm->GetComponentRotation();

	FRotator NewRotator = CurrentRotator.Add(0 , CameraVelocity * 60.f * DeltaTime, 0);

	SpringArm->SetRelativeRotation(NewRotator);
	
}

