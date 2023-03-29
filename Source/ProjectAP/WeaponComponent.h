// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Async/AsyncWork.h"
#include "WeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTAP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	UFUNCTION(BlueprintPure)
	FVector GetPlayerInputVector() { return PlayerInputVector; }

	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool Attacking) { bIsAttacking = Attacking; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void UpdateWeaponRotation(float DeltaTime);

	void OnAutoTouchEnd();
	void OnUltimateTouchEnd();

	FVector ConvertVector(FVector Input);
	

public:
	UPROPERTY(EditAnywhere)
	float LaunchOffset = 90.f;

private:
	
	UPROPERTY(EditAnywhere)
	float MinInputRate = 0.2f;

	UPROPERTY(EditAnywhere)
	float UltimateProjectileSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float AutoProjectileSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float LaunchDegree = 60.f;

	class UStaticMeshComponent* WeaponMesh;
	class USceneComponent* LocationComponent;
	class UInGameWidget* InGameWidget;
	class UInGameButton* AutoButton;
	class UInGameButton* UltimateButton;
	class UProjectileTrajectoryComponent* ProjectileTrajectory;
	class USpringArmComponent* SpringArm;
	class APlayerRobot* Owner;

	bool bIsAttacking;

	FVector WeaponRotationVector;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;

	FVector PlayerInputVector;
	FVector LastInputVector;
	
	FVector AutoInputVector;
	FVector UltimateInputVector;
	
	

};
