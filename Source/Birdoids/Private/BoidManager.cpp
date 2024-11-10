// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBoidManager::UBoidManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoidManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBoidManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ABoid* UBoidManager::SpawnBoid( TSubclassOf<ABoid> BoidClass, FTransform Transform )
{
	ABoid* NewBoid = GetWorld()->SpawnActorDeferred<ABoid>( BoidClass, Transform );

	if ( NewBoid )
	{
		UGameplayStatics::FinishSpawningActor( NewBoid, Transform );
		NewBoid->BoidManager = this;
		Boids.Add( NewBoid );
		return NewBoid;
	}

	return nullptr;
}



