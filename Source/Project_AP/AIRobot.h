// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"

#include "AIRobot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_AP_API AAIRobot : public ABasePawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AAIRobot();

	class UStaticMeshComponent* GetMeshComponent() { return BaseMesh; }
	class UStaticMeshComponent* GetWeaponMeshComponent() { return WeaponMesh; }

	/** Grants an ability at the given level, with an input code used to pick and choose which ability should be triggered. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

	/** Activates an ability with a matching input code */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 InputCode);

	class UFloatingWidget* GetFloatingBarWidget();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UFloatingWidget> UIFloatingBarClass;

	UPROPERTY()
	class UFloatingWidget* UIFloatingBar;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UWidgetComponent* UIFloatingBarComponent;

	bool IsDead();

protected:
	virtual void BeginPlay() override;

private:
	void InitializeAbilities();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* Capsule;

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

	UPROPERTY(EditAnywhere, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> AbilityList;

	void InitializeFloatingBar();

};
