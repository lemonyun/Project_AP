// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Async/AsyncWork.h"

#include "WeaponComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_AP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	void SetAutoForward(float Value) { AttackForward = Value; }
	void SetAutoRight(float Value) { AttackRight = Value; }

	float GetAutoForward() { return AttackForward; }
	float GetAutoRight() { return AttackRight; }

	void SetUltimateForward(float Value) { UltimateForward = Value; }
	void SetUltimateRight(float Value) { UltimateRight = Value; }

	float GetUltimateForward() { return UltimateForward; }
	float GetUltimateRight() { return UltimateRight; }

	FVector GetPlayerInputVector() { return PlayerInputVector; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void UpdateWeaponRotation(float DeltaTime);

	void OnAutoTouchEnd();
	void OnUltimateTouchEnd();

	void LaunchCurve();
	void LaunchStraight();

	void UltimateCheckTimer();

	//friend class FAsyncLaunchTask;

public:
	UPROPERTY(EditAnywhere)
	float LaunchOffset = 90.f;

private:
	
	UPROPERTY(EditAnywhere)
	float MinInputRate = 0.2f;

	UPROPERTY(EditAnywhere)
	float UltimateProjectileSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float AttackProjectileSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float LaunchDegree = 60.f;

	class UStaticMeshComponent* WeaponMesh;

	class UInGameWidget* InGameWidget;
	class UInGameButton* AutoButton;
	class UInGameButton* UltimateButton;

	class USceneComponent* LocationComponent;

	float AttackForward;
	float AttackRight;

	float UltimateForward;
	float UltimateRight;
	
	bool bIsAttacking;

	FVector WeaponRotationVector;

	class UProjectileTrajectoryComponent* ProjectileTrajectory;
	
	UPROPERTY()
	class AProjectile* Projectile;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	FTimerHandle UltimateHandle;
	float RepeatTime = 5;

	FVector PlayerInputVector;

	
};

//class FAsyncLaunchTask : public FNonAbandonableTask
//{
//
//public:
//
//	FAsyncLaunchTask(int32 LaunchCount, UWeaponComponent* Weapon);
//
//	FORCEINLINE TStatId GetStatId() const
//	{
//		RETURN_QUICK_DECLARE_CYCLE_STAT (FAsyncLaunchTask, STATGROUP_ThreadPoolAsyncTasks);
//	}
//
//	void DoWork();
//
//private:
//	int LaunchCount;
//
//	TObjectPtr<UWeaponComponent> WeaponPtr;
//
//};