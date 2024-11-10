// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BoidHelper.generated.h"

/*
*	This class helps simulate the boid's obstacle avoidance.
*	
*/
UCLASS()
class BIRDOIDS_API ABoidHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidHelper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float TurnFraction = 0;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float Power = 1;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	bool Draw2D = false;
	
	UPROPERTY(EditAnywhere)
	int NumOfPoints = 500;

	UPROPERTY(EditAnywhere)
	float Radius = 400;

	void PlotPoints2D();

	void PlotPoints3D();
};
