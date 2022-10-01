// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BoidHelper.generated.h"

UCLASS()
class BIRDOIDS_API ABoidHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidHelper();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnFraction = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Power = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Draw2D = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	int NumOfPoints = 5;

	UPROPERTY(EditAnywhere)
	float Radius = 200;

	UPROPERTY(EditAnywhere)
	float PointSize = 10;

	void PlotPoints2D();

	void PlotPoints3D();
};
