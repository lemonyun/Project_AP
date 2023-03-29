// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECTAP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION(BlueprintCallable)
	void SetInitialSpeed(float Speed);

	UFUNCTION(BlueprintPure)
	class UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovement; }

	/*UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float InitialSpeed;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

};
