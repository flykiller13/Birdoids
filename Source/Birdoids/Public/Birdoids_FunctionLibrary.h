// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Birdoids_FunctionLibrary.generated.h"

#define PHI (1 + FMath::Sqrt(5.0)) / 2

/**
 * 
 */
UCLASS()
class BIRDOIDS_API UBirdoids_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION( BlueprintCallable, BlueprintPure )
	static TArray<FVector> GetPointsOnSphere( int32 NumPoints, float TurnFraction, float Radius );

	UFUNCTION( BlueprintCallable, BlueprintPure )
	static TArray<FVector2D> GetPointsOnCircle(int32 NumPoints, float TurnFraction, float Radius, float Power );

	UFUNCTION( BlueprintCallable, BlueprintPure )
	static float GetPHI() { return PHI; };

};
