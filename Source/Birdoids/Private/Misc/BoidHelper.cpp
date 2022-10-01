// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/BoidHelper.h"

// Sets default values
ABoidHelper::ABoidHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoidHelper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoidHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Draw2D)
	{
		PlotPoints2D();
	}
	else
	{
		PlotPoints3D();
	}
}

void ABoidHelper::PlotPoints2D()
{
	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
	for (int i = 0; i < NumOfPoints; i++)
	{
		// 0 - 1 over the course of the loop in uniform steps.
		// The power is to make the distribution uniform. Default Power is 1,
		// However setting Power to 0.5 makes the distribution even.
		float dst =FMath::Pow(i / (NumOfPoints - 1.0f), Power) ;

		// Rotate a certain fraction of a circle.
		float angle = 2 * UKismetMathLibrary::GetPI() * TurnFraction * i;

		// Calculate x,y coordinates of Point.
		float x = dst * FMath::Cos(angle) * Radius;
		float y = dst * FMath::Sin(angle) * Radius;

		// Draw point
		DrawDebugPoint(GetWorld(), FVector(this->GetActorLocation().X + x, this->GetActorLocation().Y + y,this->GetActorLocation().Z), 5, FColor::Red, true, 9999);

	}
}

void ABoidHelper::PlotPoints3D()
{
	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
	for (int i = 0; i < NumOfPoints; i++)
	{
		// 0 - 1 over the course of the loop in uniform steps.
		// The power is to make the distribution uniform. Default Power is 1,
		// However setting Power to 0.5 makes the distribution even.
		float dst = i / (NumOfPoints - 1.0f);

		float inclination = FMath::Acos(1 - 2 * dst);

		float azimuth = 2 * UKismetMathLibrary::GetPI() * TurnFraction * i;
		// Rotate a certain fraction of a circle.

		// Calculate coordinates of Point.
		float x = FMath::Sin(inclination) * FMath::Cos(azimuth) * Radius;
		float y = FMath::Sin(inclination) * FMath::Sin(azimuth) * Radius;
		float z = FMath::Cos(inclination) * Radius;

		// Draw point
		DrawDebugPoint(GetWorld(), FVector(this->GetActorLocation().X + x, this->GetActorLocation().Y + y, this->GetActorLocation().Z + z), 5, FColor::Red, true, 9999);

	}
}

