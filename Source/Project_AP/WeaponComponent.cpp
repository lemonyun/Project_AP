// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Project_APGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "InGameWidget.h"
#include "InGameButton.h"
#include "PlayerRobot.h"
#include "ProjectileTrajectoryComponent.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	UltimateButton = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget()->GetUltimateButton();

	WeaponMesh = Cast<APlayerRobot>(GetOwner())->GetWeaponMeshComponent();
																						  
	AttackButton->OnTouchEndDelegate.BindUObject(this, &UWeaponComponent::OnAttackTouchEnd);
	UltimateButton->OnTouchEndDelegate.BindUObject(this, &UWeaponComponent::OnUltimateTouchEnd);
	
	ProjectileTrajectory = Cast<APlayerRobot>(GetOwner())->GetProjectileProjectileComponent();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// Weapon Mesh Rotation 업데이트
	FVector2D PlayerAttackInput = AttackButton->GetPlayerInput();
	FVector2D PlayerUltimateInput = UltimateButton->GetPlayerInput();

	ProjectileTrajectory->ClearTrajectory();

	if (PlayerAttackInput.Size() > KINDA_SMALL_NUMBER)
	{
		
		WeaponRotationVector = FVector(-PlayerAttackInput.Y, PlayerAttackInput.X, 0);
		UpdateWeaponRotation(DeltaTime);

		if (WeaponRotationVector.Size() > MinInputRate)
		{

			float InputPower = WeaponRotationVector.Size();
			ProjectileTrajectory->DrawTrajectory(InputPower, ProjectileSpeed, LaunchDegree, 2.f, true);

		}
	} 
	else if (PlayerUltimateInput.Size() > KINDA_SMALL_NUMBER)
	{
		WeaponRotationVector = FVector(-PlayerUltimateInput.Y, PlayerUltimateInput.X, 0);
		UpdateWeaponRotation(DeltaTime);

		if (WeaponRotationVector.Size() > MinInputRate)
		{
			ProjectileTrajectory->DrawTrajectory(1, ProjectileSpeed, 0, 1.f, false);

		}
	}
	
	


}

void UWeaponComponent::UpdateWeaponRotation(float DeltaTime)
{

	WeaponMesh->SetWorldRotation(WeaponRotationVector.Rotation());

}

void UWeaponComponent::OnAttackTouchEnd()
{

	FVector2D InputVector = AttackButton->GetPlayerInput();

	// Touch를 뗀 지점이 MinInputRate 바깥쪽인 경우 발사
	if (InputVector.Size() > MinInputRate)
	{
		// Launch
		LaunchCurve();
	}
	else
	{
		// 아무일도 일어나지 않았다..


	}
	
}

void UWeaponComponent::OnUltimateTouchEnd()
{
	FVector2D InputVector = UltimateButton->GetPlayerInput();

	// Touch를 뗀 지점이 MinInputRate 바깥쪽인 경우 발사
	if (InputVector.Size() > MinInputRate)
	{
		// Launch
		LaunchStraight();
	}
	else
	{
		// 아무일도 일어나지 않았다..


	}
}

void UWeaponComponent::LaunchCurve()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			
			FVector ProjectileVector = WeaponMesh->GetForwardVector() + FVector(0, 0, LaunchDegree / 90.f);

			const FRotator SpawnRotation = ProjectileVector.Rotation();

			const FVector SpawnLocation = Cast<APlayerRobot>(GetOwner())->GetProjectileStartPoint()->GetComponentLocation();

			FTransform ProjectileTransform = FTransform(SpawnRotation.Quaternion(), SpawnLocation);

			Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileTransform, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding);

			// 0 < InputPower < 1

			if (Projectile != nullptr)
			{
				float InputPower = WeaponRotationVector.Size();

				Projectile->SetLifeSpan(2.0f);
				Projectile->SetInitialSpeed(ProjectileSpeed * InputPower);

				Projectile->FinishSpawning(ProjectileTransform);

			}
			
		}
	}

}

void UWeaponComponent::LaunchStraight()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{

			FVector ProjectileVector = WeaponMesh->GetForwardVector();

			const FRotator SpawnRotation = ProjectileVector.Rotation();

			const FVector SpawnLocation = Cast<APlayerRobot>(GetOwner())->GetProjectileStartPoint()->GetComponentLocation();

			FTransform ProjectileTransform = FTransform(SpawnRotation.Quaternion(), SpawnLocation);

			Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileTransform, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding);

			FActorSpawnParameters a;
			// World->SpawnActor<AProjectile>()
			// 0 < InputPower < 1

			if (Projectile != nullptr)
			{
				float InputPower = WeaponRotationVector.Size();

				Projectile->SetLifeSpan(1.0f);
				Projectile->SetInitialSpeed(ProjectileSpeed);

				Projectile->GetProjectileMovement()->ProjectileGravityScale = 0;

				Projectile->FinishSpawning(ProjectileTransform);

				

			}

		}
	}
}
