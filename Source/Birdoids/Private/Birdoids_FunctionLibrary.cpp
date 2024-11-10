// Fill out your copyright notice in the Description page of Project Settings.


#include "Birdoids_FunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

TArray<FVector> UBirdoids_FunctionLibrary::GetPointsOnSphere( int32 NumPoints, float TurnFraction, float Radius )
{
	TArray<FVector> Points;

	for ( int i = 0; i < NumPoints; i++ )
	{
		// 0 - 1 over the course of the loop in uniform steps.
		float dst = i / (NumPoints - 1.0f);

		// TODO: EXPLAIN THIS.
		float inclination = FMath::Acos( 1 - 2 * dst );

		// Rotate a certain fraction of a circle.
		float azimuth = 2 * UKismetMathLibrary::GetPI() * TurnFraction * i;

		// Calculate coordinates of Point.
		float x = FMath::Sin( inclination ) * FMath::Cos( azimuth ) * Radius;
		float y = FMath::Sin( inclination ) * FMath::Sin( azimuth ) * Radius;
		float z = FMath::Cos( inclination ) * Radius;

		FVector Point = FVector( x, y, z );
		Points.Add( Point );
	}

	return Points;
}

TArray<FVector2D> UBirdoids_FunctionLibrary::GetPointsOnCircle( int32 NumPoints, float TurnFraction, float Radius, float Power )
{
	TArray<FVector2D> Points;

	for ( int i = 0; i < NumPoints; i++ )
	{
		// 0 - 1 over the course of the loop in uniform steps.
		// The power is to make the distribution uniform. Default Power is 1,
		// However setting Power to 0.5 makes the distribution even.
		float dst = FMath::Pow( i / (NumPoints - 1.0f), Power );

		// Rotate a certain fraction of a circle.
		float angle = 2 * UKismetMathLibrary::GetPI() * TurnFraction * i;

		// Calculate x,y coordinates of Point.
		float x = dst * FMath::Cos( angle ) * Radius;
		float y = dst * FMath::Sin( angle ) * Radius;

		FVector2D Point = FVector2D( x, y );
		Points.Add( Point );

	}

	return Points;
}
