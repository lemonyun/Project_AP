// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRobot.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RobotMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "WeaponComponent.h"
#include "ProjectileTrajectoryComponent.h"
#include "Components/SceneComponent.h"
#include "Project_APGameInstance.h"
#include "PlayerHUD.h"
#include "RobotPlayerController.h"

#include "AbilitySystemComponent.h"
#include "RobotAttributeSet.h"



APlayerRobot::APlayerRobot()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	MovementComponent = CreateDefaultSubobject<URobotMovementComponent>(TEXT("MovementComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	ProjectileStartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileStartPoint"));
	ProjectileTrajectory = CreateDefaultSubobject<UProjectileTrajectoryComponent>(TEXT("ProjectileTrajectory"));

	
	RootComponent = Capsule;
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);
	BaseMesh->SetupAttachment(Capsule);
	WeaponMesh->SetupAttachment(BaseMesh);
	ProjectileStartPoint->SetupAttachment(WeaponMesh);


	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));


}




void APlayerRobot::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
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

void APlayerRobot::ActivateAbility(int32 InputCode)
{
	if (IsValid(AbilitySystem))
	{
		AbilitySystem->AbilityLocalInputPressed(InputCode);
	}
}

void APlayerRobot::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystem->InitAbilityActorInfo(this, this);
	if (IsValid(AbilitySystem))
	{
		AttributeSet = AbilitySystem->GetSet<URobotAttributeSet>();
	}
	
	// ¾îºô¸®Æ¼ Grant
	InitializeAbilities();

	InitializeHUD();

	ActivateAbility(2);
	ActivateAbility(3);

}

void APlayerRobot::InitializeAbilities()
{
	for (int i = 0; i < AbilityList.Num(); i++)
	{
		GrantAbility(AbilityList[i], 1, i);
	}
}

void APlayerRobot::InitializeHUD()
{
	UPlayerHUD* HUD = Cast<ARobotPlayerController>(GetController())->GetInGameWidget()->GetPlayerHUD();

	
	HUD->UltimateSetPercent(AttributeSet->GetUltimateMana() / AttributeSet->GetUltimateManaMax());
	HUD->AutoSetPercent(AttributeSet->GetAutoMana() / AttributeSet->GetAutoManaMax());
	HUD->HealthSetPercent(AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());
}

