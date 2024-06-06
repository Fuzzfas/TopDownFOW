// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelFloorActor.h"

// Sets default values
ALevelFloorActor::ALevelFloorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LevelFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LevelFloorMesh"));
	RootComponent = LevelFloorMesh;

	FloorSize = FVector::ZeroVector;

}

// Called when the game starts or when spawned
void ALevelFloorActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the size of the floor mesh
	if (LevelFloorMesh)
	{
		// Get the size of the floor mesh
		//FloorSize = LevelFloorMesh->CalcBounds(LevelFloorMesh->GetRelativeTransform()).BoxExtent;
		FloorSize = LevelFloorMesh->GetRelativeScale3D();

		UE_LOG(LogTemp, Warning, TEXT("FloorSize = %s"), *FloorSize.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FloorSize = null"));
	}

}

// Called every frame
void ALevelFloorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelFloorActor::PostInitProperties()
{

	Super::PostInitProperties();



	

}

const FVector ALevelFloorActor::GetMeshSize() const
{
	return FloorSize;
}



