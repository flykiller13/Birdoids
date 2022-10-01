// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/RayCalculator.h"

// Sets default values for this component's properties
URayCalculator::URayCalculator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void URayCalculator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URayCalculator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Returns points on sphere in LOCAL SPACE ON UNIT SPHERE.
TArray<FVector> URayCalculator::GetPointsOnSphere()
{
	TArray<FVector> Points;
	float phi = (1 + FMath::Sqrt(5.0)) / 2;
	float TurnFraction = UKismetMathLibrary::GetPI() * 2 * phi;

	for (int i = 0; i < NumOfPoints; i++)
	{
		// 0 - 1 over the course of the loop in uniform steps.
		float dst = (float) i / NumOfPoints;

		// TODO: EXPLAIN THIS.
		float inclination = FMath::Acos(1 - 2 * dst);

		// TODO: EXPLAIN THIS.
		float azimuth = TurnFraction * i;

		// Calculate coordinates of Point.
		float x = FMath::Sin(inclination) * FMath::Cos(azimuth);
		float y = FMath::Sin(inclination) * FMath::Sin(azimuth);
		float z = FMath::Cos(inclination);
		FVector Point = FVector(x, y, z);
		
		Points.Add(Point);
	}

	return Points;
}

