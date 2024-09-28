// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "RenderUtils.h"
#include "Engine/TextureDefines.h"
#include "Materials/MaterialInstanceDynamic.h" // Ensure this is included for dynamic materials
#include "DrawDebugHelpers.h"
#include "FogOfWarActor.generated.h"

UCLASS(Blueprintable)
class TOPDOWNFOW_API AFogOfWarActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogOfWarActor();
	~AFogOfWarActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void UpdateFogOfWarTexture();
	//void UpdateVisibilityGrid(const FVector2D& PlayerGridPosition);
	void UpdateMeshSize(const FVector& FloorSize);
	void DrawDebugConeFOW(FVector2D UnitPosition, FVector2D UnitDirection, float ConeAngle, float VisionRange);
	void SetFogVisibility(FVector Position, FVector Direction, float FieldOfViewAngle, float VisionRange, float Opacity);
	void InitializeRevealedTexture();
	bool IsWithinCone(FVector2D PixelPos, FVector2D UnitPos2D, FVector2D UnitDir2D, float FieldOfViewAngle, float VisionRange);
	void UpdatePreviouslyRevealedTexture(FVector Position, FVector Direction, float FieldOfViewAngle, float VisionRange, float Opacity);
	void UpscaleLowToHighRes(uint8& LowResPixel, FVector2D PixelPos);
	void CopyToTexture();

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

	UPROPERTY()
	UTexture2D* PreviouslyRevealedTexture;

private:
	uint8* LowResData;
	uint8* HighResData;
	int32 LowResTextureSizeX;
	int32 LowResTextureSizeY;
	int32 HighResTextureSizeX;
	int32 HighResTextureSizeY;
	int32 ScaleFactorX;
	int32 ScaleFactorY;

	uint8 HalfGrayColor = 0;
	//FColor HalfGrayColor = FColor(128, 128, 128, 255); // (R, G, B, A) - 128 is 0.5 in normalized form
	int WorldToTextureScale = 10; //The world is this factor larger than the low res texture
};
