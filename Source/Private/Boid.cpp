// Fill out your copyright notice in the Description page of Project Settings.

#include "Boid.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "BoidManager.h"
#include "Engine/World.h"

// Sets default values
ABoid::ABoid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components and set attachment
	RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "Root" ) );

	BoidMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Boid Mesh" ) );
	BoidMesh->SetupAttachment( RootComponent );

	VisionSphere = CreateDefaultSubobject<USphereComponent>( TEXT( "Vision Sphere" ) );
	VisionSphere->SetupAttachment( RootComponent );

	VisionRange = VisionSphere->GetScaledSphereRadius();
}

// Called when the game starts or when spawned
// Sets random values for Velocity and Speed.
void ABoid::BeginPlay()
{
	Super::BeginPlay();

	if ( bOverrideStart )
	{
		// Update velocity
		CurrentVelocity = StartDir * StartSpeed;
	}
	else
	{
		// Give the boid a random direction and speed
		CurrentVelocity = FMath::VRand() * ((MaxSpeed + MinSpeed) / 2);
	}

	// Set vision range
	VisionRange = VisionSphere->GetScaledSphereRadius();
}

// Called every frame
void ABoid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector FlockVel( 0 );
	FVector FlockCenter( 0 );
	FVector SeparationForce( 0 );

	if ( BoidManager )
	{

		FlockVel = GetFlockVelocity() * AlignmentWeight;

		FlockCenter = GetOffsetToFlockCenter() * CohesionWeight;

		SeparationForce = GetSeparationForce() * SeparationWeight;

	}

	CurrentVelocity += FlockVel + FlockCenter + SeparationForce; // Add rules to velocity
	CurrentVelocity += ( GetAttractionPointForce() * AttractionPointWeight ); // Add force to move towards the attraction point (if exists)

	// Steer away from obstacles
	FHitResult Hit;
	if ( IsObstacleAhead( Hit ) )
	{
		CurrentVelocity += GetUnobstructedDir( Hit ) * ObstacleAvoidanceWeight;
	}

	CurrentVelocity = CurrentVelocity.GetClampedToSize( MinSpeed, MaxSpeed ); // Clamp velocity to min-max speed

	float InterpSpeed = 10;

	//Moves the Boid
	FVector TargetLocation = GetActorLocation() + CurrentVelocity;
	FVector NewLocation = FMath::VInterpTo( GetActorLocation(), TargetLocation, DeltaTime, InterpSpeed );
	SetActorLocation( NewLocation );

	//Makes Rot from Z cause Boid mesh points to Z direction
	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromZ( CurrentVelocity );
	FRotator NewRotation = FMath::RInterpTo( BoidMesh->GetRelativeRotation(), TargetRotation, DeltaTime, InterpSpeed );
	BoidMesh->SetRelativeRotation( NewRotation );
}

// Return Current Velocity.
FVector ABoid::GetCurrentVelocity()
{
	return CurrentVelocity;
}

FVector ABoid::GetOffsetToFlockCenter_Implementation()
{
	FVector Center( 0 );
	int32 FlockCounter = 0;

	if ( !BoidManager->Boids.IsEmpty() )
	{
		for ( auto& TempBoid : BoidManager->Boids )
		{
			FVector Offset = GetActorLocation() - TempBoid->GetActorLocation();
			if ( TempBoid != this && Offset.Length() <= VisionRange )
			{
				Center += TempBoid->GetActorLocation();
				FlockCounter++;
			}
		}
		if ( FlockCounter > 0 )
		{
			Center /= FlockCounter;
			return (Center - GetActorLocation()) / 10;
		}
		
		return GetActorLocation(); // Only boid in the flock, center of flock is boid itself
	}

	return Center;
}

FVector ABoid::GetFlockVelocity_Implementation()
{
	FVector AvgVelocity( 0 );
	int32 FlockCounter = 0;

	if ( !BoidManager->Boids.IsEmpty() )
	{
		for ( auto& TempBoid : BoidManager->Boids )
		{
			FVector Offset = GetActorLocation() - TempBoid->GetActorLocation();
			if ( TempBoid != this && Offset.Length() <= VisionRange )
			{
				AvgVelocity += TempBoid->CurrentVelocity;
				FlockCounter++;
			}
		}
		if ( FlockCounter > 0 )
			AvgVelocity /= FlockCounter;
	}

	return (AvgVelocity-GetCurrentVelocity())/5;
}

// Returns a vector that encourages the Boid to steer AWAY from nearby Boids.
FVector ABoid::GetSeparationForce_Implementation()
{
	FVector SeparationDir( 0 );

	for ( auto& Boid : BoidManager->Boids )
	{
		if ( Boid != this )
		{
			FVector Offset = Boid->GetActorLocation() - this->GetActorLocation();

			if ( Offset.SquaredLength() <= SeparationRange*SeparationRange )
			{
				SeparationDir -= Offset;
			}
		}
	}

	return SeparationDir/10;
}

FVector ABoid::GetAttractionPointForce_Implementation()
{
	FVector Offset( 0 );

	if ( AttractionPoint )
	{
		Offset = AttractionPoint->GetActorLocation() - this->GetActorLocation();
	}

	return Offset/100;
}

FVector ABoid::GetUnobstructedDir_Implementation( FHitResult Hit )
{
	FVector Offset = Hit.ImpactPoint - GetActorLocation();
	float Dot = GetCurrentVelocity().Dot( Offset );
	FVector UnobstructedDir( 0 );

	if ( Dot <= 0 )
	{
		UnobstructedDir = GetCurrentVelocity() + Hit.Normal*ObstacleAvoidanceForceMultiplier;
	}
	else
	{
		UnobstructedDir = Hit.Normal*ObstacleAvoidanceForceMultiplier;
	}

	return UnobstructedDir;
}

// Returns true if theres some object ahead, false otherwise.
bool ABoid::IsObstacleAhead_Implementation( FHitResult& Hit )
{
	// Trace settings
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor( this );
	// CollisionParams.bTraceComplex = true;

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + CurrentVelocity.GetSafeNormal() * ObstacleAvoidanceRange;

	FVector MeshBounds = BoidMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();
	float SphereRadius = (BoidMesh->GetComponentScale().X * MeshBounds.X) / 2;
	FCollisionShape MySphere = FCollisionShape::MakeSphere( SphereRadius );

	return GetWorld()->SweepSingleByChannel( Hit, TraceStart, TraceEnd, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1, MySphere, CollisionParams );
}

