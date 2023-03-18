// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_AP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	void SetAttackForward(float Value);
	void SetAttackRight(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void UpdateWeaponRotation(float DeltaTime);

	void OnTouchEnd();

	void Launch();

private:
	
	UPROPERTY(EditAnywhere)
	float MinInputRate = 0.2f;

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 500.f;

	UPROPERTY(EditAnywhere)
	float ProjectileDegree = 45.f;

	class UStaticMeshComponent* WeaponMesh;

	class UInGameWidget* InGameWidget;
	class UInGameButton* AttackButton;

	float AttackForward;
	float AttackRight;

	FVector WeaponRotationVector;

	class UProjectileTrajectoryComponent* ProjectileTrajectory;
	
	UPROPERTY()
	class AProjectile* Projectile;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileClass;



};
