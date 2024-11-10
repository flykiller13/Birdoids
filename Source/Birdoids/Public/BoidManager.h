// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Boid.h"
#include "BoidManager.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BIRDOIDS_API UBoidManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoidManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite )
		TArray<ABoid*> Boids;

	UFUNCTION( BlueprintCallable )
	ABoid* SpawnBoid( TSubclassOf<ABoid> BoidClass, FTransform Transform);

};
