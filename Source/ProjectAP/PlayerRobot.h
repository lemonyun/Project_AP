// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"

#include "PlayerRobot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAP_API APlayerRobot : public ABasePawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerRobot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class URobotMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* WeaponComponent;

	class UProjectileTrajectoryComponent* GetProjectileProjectileComponent() { return ProjectileTrajectory; }
	class UWeaponComponent* GetWeaponComponent() { return WeaponComponent; }
	class UStaticMeshComponent* GetMeshComponent() { return BaseMesh; }
	class UStaticMeshComponent* GetWeaponMeshComponent() { return WeaponMesh; }

	UFUNCTION(BlueprintPure)
	class USceneComponent* GetProjectileStartPoint() { return ProjectileStartPoint; }
	class USpringArmComponent* GetSpringArmComponent() { return SpringArm; }

	/** Grants an ability at the given level, with an input code used to pick and choose which ability should be triggered. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

	/** Activates an ability with a matching input code */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 InputCode);

	///** Cancels abilities with specific Gameplay Tags applied to them.*/
	//UFUNCTION(BlueprintCallable, Category = "Abilities")
	//void CancelAbilityWithTags(const FGameplayTagContainer CancelWithTags);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void InitializeAbilities();
	// void Move(FVector Value);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileTrajectoryComponent* ProjectileTrajectory;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileStartPoint;

	UPROPERTY(EditAnywhere)
	class UAbilitySystemComponent* AbilitySystem;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}

	UPROPERTY()
	const class URobotAttributeSet* AttributeSet;

	// 블루프린트에서 어빌리티 Add 해줘야 함
	UPROPERTY(EditAnywhere, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> AbilityList;
	
	void InitializeHUD();
};
