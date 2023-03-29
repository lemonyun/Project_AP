// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileTrajectoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTAP_API UProjectileTrajectoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileTrajectoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DrawTrajectory(float Power, float ProjectileSpeed, float Angle, float Time, float bIsCurve);

	void ClearTrajectory();

private:
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* Decal;

	class USceneComponent* ProjectileStartPoint;

	class UWeaponComponent* Weapon;

	bool isAiming = false;

	UClass* SplineMeshClass;

	UStaticMesh* StaticMesh;
};
