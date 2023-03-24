// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRobot.h"

#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RobotMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "WeaponComponent.h"
#include "ProjectileTrajectoryComponent.h"
#include "Components/SceneComponent.h"

#include "AbilitySystemComponent.h"
#include "RobotAttributeSet.h"



AAIRobot::AAIRobot()
{
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	ProjectileStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileStartPoint"));
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));

	RootComponent = Capsule;
	BaseMesh->SetupAttachment(Capsule);
	WeaponMesh->SetupAttachment(BaseMesh);
	ProjectileStartPoint->SetupAttachment(WeaponMesh);

}




void AAIRobot::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{

	if (GetLocalRole() == ROLE_Authority && IsValid(AbilitySystem) && IsValid(AbilityClass))
	{
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();
		if (IsValid(Ability))
		{
			// create the new ability spec struct. Ability specs contain metadata about the ability, like what level they're set to, as well as a reference to the ability.
			FGameplayAbilitySpec AbilitySpec(
				Ability,
				Level,
				InputCode
			);

			AbilitySystem->GiveAbility(AbilitySpec);
		}
	}

}

void AAIRobot::ActivateAbility(int32 InputCode)
{
	if (IsValid(AbilitySystem))
	{
		AbilitySystem->AbilityLocalInputPressed(InputCode);
	}
}

void AAIRobot::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystem->InitAbilityActorInfo(this, this);
	if (IsValid(AbilitySystem))
	{
		AttributeSet = AbilitySystem->GetSet<URobotAttributeSet>();
	}

	// ¾îºô¸®Æ¼ Grant
	InitializeAbilities();

}

void AAIRobot::InitializeAbilities()
{
	for (int i = 0; i < AbilityList.Num(); i++)
	{
		GrantAbility(AbilityList[i], 1, i);
	}
}



