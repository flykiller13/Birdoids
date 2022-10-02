// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.h"
#include "BoidSpawner.generated.h"

UCLASS()
class BIRDOIDS_API ABoidSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoidSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		int32 BoidsToSpawn = 5;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		TSubclassOf<ABoid> BoidClass;

	UFUNCTION( BlueprintCallable )
		void SpawnBoids();

};
