// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/BoidHelper.h"
#include "Birdoids_FunctionLibrary.h"

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

	TArray<FVector2D> Points = UBirdoids_FunctionLibrary::GetPointsOnCircle( NumOfPoints, TurnFraction, Radius, Power );

	for ( FVector2D Point : Points )
	{
		FVector Pos = FVector( this->GetActorLocation().X + Point.X, this->GetActorLocation().Y + Point.Y, this->GetActorLocation().Z );
		DrawDebugPoint( GetWorld(), Pos, 5, FColor::Red );
	}
}

void ABoidHelper::PlotPoints3D()
{
	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());

	TArray<FVector> Points = UBirdoids_FunctionLibrary::GetPointsOnSphere( NumOfPoints, TurnFraction, Radius );

	for ( FVector Point : Points )
	{
		FVector Pos = FVector( this->GetActorLocation().X + Point.X, this->GetActorLocation().Y + Point.Y, this->GetActorLocation().Z + Point.Z );
		DrawDebugPoint( GetWorld(), Pos, 5, FColor::Red );
	}
}

