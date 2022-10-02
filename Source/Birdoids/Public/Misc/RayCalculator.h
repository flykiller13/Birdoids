// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet//KismetMathLibrary.h"
#include "RayCalculator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIRDOIDS_API URayCalculator : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URayCalculator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		TArray<FVector> GetPointsOnSphere();

private:
	UPROPERTY(EditAnywhere)
	int NumOfPoints = 300;
};
