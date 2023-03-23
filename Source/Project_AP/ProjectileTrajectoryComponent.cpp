// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileTrajectoryComponent.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/DecalComponent.h"
#include "PlayerRobot.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.h"

// Sets default values for this component's properties
UProjectileTrajectoryComponent::UProjectileTrajectoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");

	// SplineMesh = CreateDefaultSubobject<USplineMeshComponent>("SplineMesh");

	Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
	Decal->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SplineMeshOb(TEXT("StaticMesh'/Game/Gameplay/Meshes/Box_100_10_10_StaticMesh.Box_100_10_10_StaticMesh'"));

	StaticMesh = SplineMeshOb.Object;
}


// Called when the game starts
void UProjectileTrajectoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// UE_LOG(LogTemp, Warning, TEXT("hello %s"), *SplineTemplateName.ToString());

	APlayerRobot* Owner = Cast<APlayerRobot>(GetOwner());

	if (Owner != nullptr)
	{
		ProjectileStartPoint = Owner->GetProjectileStartPoint();

		Weapon = Owner->GetWeaponComponent();
	}

	
}


// Called every frame
void UProjectileTrajectoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileTrajectoryComponent::DrawTrajectory(float InputPower, float ProjectileSpeed, float Angle, float Time, float bIsCurve)
{
	FPredictProjectilePathParams Params;

	if(Weapon == nullptr) return;

	// UE_LOG(LogTemp, Warning, TEXT("ProjectileSpeed in Trag %f"), ProjectileSpeed);

	FVector PlayerInputVector = Weapon->GetPlayerInputVector();

	Params.LaunchVelocity = InputPower * ProjectileSpeed * (PlayerInputVector.GetSafeNormal() + FVector(0, 0, Angle / 90.f));
	Params.StartLocation = ProjectileStartPoint->GetComponentLocation() + PlayerInputVector.GetSafeNormal() * Weapon->LaunchOffset;
	
	Params.ProjectileRadius = 0;
	Params.TraceChannel = ECC_WorldStatic;
	Params.bTraceWithCollision = true;
	Params.bTraceComplex = false;

	if (!bIsCurve)
	{
		Params.OverrideGravityZ = 0.01f;
	}
	
	TArray<AActor*> ActorsToIgnore = {GetOwner()};
	Params.ActorsToIgnore = ActorsToIgnore;
	Params.DrawDebugType = EDrawDebugTrace::None;
	Params.SimFrequency = 15.f;
	Params.MaxSimTime = Time;

	FPredictProjectilePathResult Results;

	UGameplayStatics::PredictProjectilePath(this, Params, Results);

	Decal->SetVisibility(true);
	Decal->SetWorldLocation(Results.LastTraceDestination.Location);

	// UE_LOG(LogTemp, Warning, TEXT("FF %f"), Results.HitResult.Distance);

	for (int i = 0; i < Results.PathData.Num(); i++)
	{
		FPredictProjectilePathPointData Point = Results.PathData[i];

		Spline->AddSplinePointAtIndex(Point.Location, i, ESplineCoordinateSpace::Local, true);
		
	}


	// Results.HitResult.

	int32 NumPoints = Spline->GetNumberOfSplinePoints();

	for (int i = 0; i < NumPoints - 1; i++)
	{

		USplineMeshComponent *SplineMesh = NewObject<USplineMeshComponent>(GetOwner());
		SplineMesh->SetStaticMesh(StaticMesh);

		SplineMesh->RegisterComponent();
		GetOwner()->AddInstanceComponent(SplineMesh);

		// UE_LOG(LogTemp, Warning, TEXT("%s"), *SplineMesh->GetName());
		
		if (SplineMesh == nullptr)
		{	
			UE_LOG(LogTemp, Warning, TEXT("splinemesh error"));
			return;
		}

		FVector StartPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector EndPos = Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		FVector StartTangent = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FVector EndTangent = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);

		SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);

	}
}

void UProjectileTrajectoryComponent::ClearTrajectory()
{
	Spline->ClearSplinePoints(true);

	GetOwner()->ClearInstanceComponents(true);

	Decal->SetVisibility(false);
}

