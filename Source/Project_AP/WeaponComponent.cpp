// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Project_APGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "InGameWidget.h"
#include "InGameButton.h"
#include "PlayerRobot.h"
#include "ProjectileTrajectoryComponent.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AProjectile> ProjectileBPClass (TEXT("/Game/Gameplay/Actors/BP_Projectile"));

	ProjectileClass = ProjectileBPClass.Class;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	AttackButton = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget()->GetAttackButton();

	WeaponMesh = Cast<APlayerRobot>(GetOwner())->GetWeaponMeshComponent();

	AttackButton->OnTouchEndDelegate.BindUObject(this, &UWeaponComponent::OnTouchEnd);
	
	ProjectileTrajectory = Cast<APlayerRobot>(GetOwner())->GetProjectileProjectileComponent();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// Weapon Mesh Rotation 업데이트
	FVector2D PlayerAttackInput = AttackButton->GetPlayerInput();

	AttackForward = -PlayerAttackInput.Y;
	AttackRight = PlayerAttackInput.X;

	WeaponRotationVector = FVector(AttackForward, AttackRight, 0);

	

	if (WeaponRotationVector != FVector::ZeroVector)
	{
		UpdateWeaponRotation(DeltaTime);	
	}

	ProjectileTrajectory->ClearTrajectory();

	if (WeaponRotationVector.Size() > MinInputRate)
	{
		
		float InputPower = WeaponRotationVector.Size();
		ProjectileTrajectory->DrawTrajectory(InputPower, ProjectileSpeed, ProjectileDegree);
		
	}

}

void UWeaponComponent::SetAttackForward(float Value)
{
	AttackForward = Value;
}

void UWeaponComponent::SetAttackRight(float Value)
{
	AttackRight = Value;
}


void UWeaponComponent::UpdateWeaponRotation(float DeltaTime)
{

	WeaponMesh->SetWorldRotation(WeaponRotationVector.Rotation());

}

void UWeaponComponent::OnTouchEnd()
{

	FVector2D InputVector = AttackButton->GetPlayerInput();

	// Touch를 뗀 지점이 MinInputRate 바깥쪽인 경우 발사
	if (InputVector.Size() > MinInputRate)
	{
		// Launch
		UE_LOG(LogTemp, Warning, TEXT("size %f"), InputVector.Size());
		UE_LOG(LogTemp, Warning, TEXT("Launch"));

		Launch();

		
	}
	else
	{
		// 아무일도 일어나지 않았다..
		UE_LOG(LogTemp, Warning, TEXT("size %f"), InputVector.Size());
		UE_LOG(LogTemp, Warning, TEXT("Cancel"));

	}
	
}

void UWeaponComponent::Launch()
{
	// UE_LOG(LogTemp, Warning, TEXT("ProjectileClass %s"), *ProjectileClass->GetName());
	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			
			FVector ProjectileVector = WeaponMesh->GetForwardVector() + FVector(0, 0, ProjectileDegree / 90.f);

			const FRotator SpawnRotation = ProjectileVector.Rotation();

			const FVector SpawnLocation = Cast<APlayerRobot>(GetOwner())->GetProjectileStartPoint()->GetComponentLocation();

			//Set Spawn Collision Handling Override

			FTransform ProjectileTransform = FTransform(SpawnRotation.Quaternion(), SpawnLocation);

			Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileTransform, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding);

			// 0 < InputPower < 1

			if (Projectile != nullptr)
			{
				float InputPower = WeaponRotationVector.Size();
				UE_LOG(LogTemp, Warning, TEXT("Input Power %f"), InputPower);
				UE_LOG(LogTemp, Warning, TEXT("ProjectileSpeed in Launch %f"), ProjectileSpeed);

				Projectile->SetInitialSpeed(ProjectileSpeed * InputPower);

				Projectile->FinishSpawning(ProjectileTransform);

			}
			
		}
	}

}
