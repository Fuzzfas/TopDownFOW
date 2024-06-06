// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogOfWarActor.generated.h"

UCLASS(Blueprintable)
class TOPDOWNFOW_API AFogOfWarActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogOfWarActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void UpdateFogOfWarTexture();
	//void UpdateVisibilityGrid(const FVector2D& PlayerGridPosition);
	void UpdateMeshSize(const FVector& FloorSize);
	void SetFogVisibility(FVector Position, FVector Direction, float FieldOfViewAngle, float VisionRange, float Opacity);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
	UMaterialInstanceDynamic* DynamicMaterialInstance = nullptr;

	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* FogOfWarMesh;



	FVector FogSize;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
	UTexture2D* FogOfWarTexture;

	TArray<TArray<bool>> VisibilityGrid;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fog of War")
	//float FieldOfViewAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fog of War")
	int32 RayCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fog of War")
	FVector FogHeight;

};
