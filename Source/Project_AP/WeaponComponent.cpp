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
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	AutoButton = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget()->GetAutoButton();
	UltimateButton = Cast<UProject_APGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetInGameWidget()->GetUltimateButton();

	

	Owner = Cast<APlayerRobot>(GetOwner());
	if (Owner != nullptr)
	{
		WeaponMesh = Owner->GetWeaponMeshComponent();
		// Mesh = Owner->GetMeshComponent();
		SpringArm = Owner->GetSpringArmComponent();
		ProjectileTrajectory = Owner->GetProjectileProjectileComponent();
		LocationComponent = Owner->GetProjectileStartPoint();
	}
																						  
	AutoButton->OnTouchEndDelegate.BindUObject(this, &UWeaponComponent::OnAutoTouchEnd);
	UltimateButton->OnTouchEndDelegate.BindUObject(this, &UWeaponComponent::OnUltimateTouchEnd);
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// Weapon Mesh Rotation 업데이트

	FVector2D PlayerAutoInput = AutoButton->GetPlayerInput();
	FVector2D PlayerUltimateInput = UltimateButton->GetPlayerInput();

	AutoInputVector = FVector(-PlayerAutoInput.Y, PlayerAutoInput.X, 0);
	UltimateInputVector = FVector(-PlayerUltimateInput.Y, PlayerUltimateInput.X, 0);

	AutoInputVector = ConvertVector(AutoInputVector);
	UltimateInputVector = ConvertVector(UltimateInputVector);

	
	if (PlayerAutoInput.Size() > PlayerUltimateInput.Size())
	{
		PlayerInputVector = AutoInputVector;
	}
	else
	{
		PlayerInputVector = UltimateInputVector;
	}



	ProjectileTrajectory->ClearTrajectory();

	// WeaponMesh 회전 업데이트
	if (PlayerInputVector.Size() > KINDA_SMALL_NUMBER && !bIsAttacking) // 
	{
		WeaponRotationVector = PlayerInputVector;
		UpdateWeaponRotation(DeltaTime);
	}

	// 공격 중인 경우에는 WeaponMesh의 회전을 유지
	if (bIsAttacking)
	{
		WeaponRotationVector = LastInputVector;
		UpdateWeaponRotation(DeltaTime);
	}

	// 궤적 업데이트
	if (PlayerAutoInput.Size() > KINDA_SMALL_NUMBER && PlayerAutoInput.Size() > MinInputRate)
	{
		float InputPower = PlayerAutoInput.Size();
		ProjectileTrajectory->DrawTrajectory(InputPower, AutoProjectileSpeed, LaunchDegree, 2.f, true);

	} 
	else if (PlayerUltimateInput.Size() > KINDA_SMALL_NUMBER && PlayerUltimateInput.Size() > MinInputRate)
	{
		ProjectileTrajectory->DrawTrajectory(1, UltimateProjectileSpeed, 0, 1.f, false);
	}


}

void UWeaponComponent::UpdateWeaponRotation(float DeltaTime)
{
	WeaponMesh->SetWorldRotation(WeaponRotationVector.Rotation());

}

void UWeaponComponent::OnAutoTouchEnd()
{

	FVector2D InputVector = AutoButton->GetPlayerInput();

	// Touch를 뗀 지점이 MinInputRate 바깥쪽인 경우 발사
	if (InputVector.Size() > MinInputRate)
	{
		
		
		// Launch
		// LaunchCurve();
		
		Owner->ActivateAbility(0);
	}
	else
	{
		// 아무일도 일어나지 않았다..


	}
	
}

void UWeaponComponent::OnUltimateTouchEnd()
{
	// FVector2D InputVector = UltimateButton->GetPlayerInput();

	// Touch를 뗀 지점이 MinInputRate 바깥쪽인 경우 발사
	if (UltimateInputVector.Size() > MinInputRate)
	{
		// Launch
		/*AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [&]()
		{
			auto Task = new FAsyncTask<FAsyncLaunchTask>(10, this);
			Task->StartBackgroundTask();
			Task->EnsureCompletion();
			delete Task;

			UE_LOG(LogTemp, Log, TEXT("Stop Task"));


		});*/

		// 

		Owner->ActivateAbility(1);
	
		if (!GetOwner()->GetWorldTimerManager().IsTimerActive(UltimateHandle))
		{
			RepeatTime = 5.f;
			bIsAttacking = true;
			LastInputVector = UltimateInputVector;
			GetOwner()->GetWorldTimerManager().SetTimer(UltimateHandle, this, &UWeaponComponent::UltimateCheckTimer, 0.1f, true);
		}



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
			
			//FVector ProjectileVector = WeaponMesh->GetForwardVector() + FVector(0, 0, LaunchDegree / 90.f);
			FVector ProjectileVector = PlayerInputVector.GetSafeNormal() + FVector(0, 0, LaunchDegree / 90.f);

			const FRotator SpawnRotation = ProjectileVector.Rotation();

			const FVector SpawnLocation = LocationComponent->GetComponentLocation() + PlayerInputVector.GetSafeNormal() * LaunchOffset;

			FTransform ProjectileTransform = FTransform(SpawnRotation.Quaternion(), SpawnLocation);

			Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileTransform, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding);
		
			// 0 < InputPower < 1

			if (Projectile != nullptr)
			{
				float InputPower = WeaponRotationVector.Size();

				Projectile->SetLifeSpan(2.0f);
				Projectile->SetInitialSpeed(AutoProjectileSpeed * InputPower);

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

			const FVector SpawnLocation = LocationComponent->GetComponentLocation() + ProjectileVector * LaunchOffset;

			FTransform ProjectileTransform = FTransform(SpawnRotation.Quaternion(), SpawnLocation);

			Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileTransform, GetOwner(), Cast<APawn>(GetOwner()), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding);

			FActorSpawnParameters a;
			// World->SpawnActor<AProjectile>()
			// 0 < InputPower < 1

			if (Projectile != nullptr)
			{
				float InputPower = WeaponRotationVector.Size();

				Projectile->SetLifeSpan(1.0f);
				Projectile->SetInitialSpeed(UltimateProjectileSpeed);

				Projectile->GetProjectileMovement()->ProjectileGravityScale = 0;

				Projectile->FinishSpawning(ProjectileTransform);

				

			}

		}
	}
}

FVector UWeaponComponent::ConvertVector(FVector Input)
{
	FRotator SpringArmRotator = SpringArm->GetRelativeRotation();
	SpringArmRotator.Pitch = 0;

	FVector ConvertedVector = SpringArmRotator.Quaternion().RotateVector(Input);

	return ConvertedVector;

}

void UWeaponComponent::UltimateCheckTimer()
{
	// GetOwner()->GetWorldTimerManager().IsTimerActive(UltimateHandle)
	if (--RepeatTime <= 0)
	{
		bIsAttacking = false;
		GetOwner()->GetWorldTimerManager().ClearTimer(UltimateHandle);
	}

	LaunchStraight();

}


//void FAsyncLaunchTask::DoWork()
//{
//	while (LaunchCount > 0)
//	{
//		WeaponPtr->LaunchStraight();
//		FPlatformProcess::Sleep(0.1f);
//		
//	}
//}
//
//FAsyncLaunchTask::FAsyncLaunchTask(int32 LaunchCount, UWeaponComponent* Weapon)
//{
//	WeaponPtr = Weapon;
//	this->LaunchCount = LaunchCount;
//
//}