// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidSpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoidSpawner::ABoidSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoidSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnBoids();
	
}

// Called every frame
void ABoidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoidSpawner::SpawnBoids()
{
	for ( int i = 0; i < BoidsToSpawn; i++ )
	{
		ABoid* NewBoid = GetWorld()->SpawnActorDeferred<ABoid>( BoidClass, GetActorTransform());

		if ( NewBoid )
		{
			NewBoid->AttractionPoint = this;
			UGameplayStatics::FinishSpawningActor( NewBoid, GetActorTransform() );
		}
	}
}

