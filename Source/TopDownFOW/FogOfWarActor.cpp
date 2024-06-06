// Fill out your copyright notice in the Description page of Project Settings.


#include "FogOfWarActor.h"

// Sets default values
AFogOfWarActor::AFogOfWarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FogOfWarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FogOfWarMesh"));
	RootComponent = FogOfWarMesh;

	FogOfWarTexture = nullptr;

	//FieldOfViewAngle = 90.0f;	
	RayCount = 360;


}

// Called when the game starts or when spawned
void AFogOfWarActor::BeginPlay()
{
	Super::BeginPlay();

	if (FogOfWarMesh)
	{
    // Get the material applied to the static mesh
    UMaterialInterface* Material = FogOfWarMesh->GetMaterial(0);
	 DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
	 FogOfWarMesh->SetMaterial(0, DynamicMaterialInstance);


	 // Array to store the textures used by the material
	 //TArray<UTexture*> UsedTextures;

	 // Call GetUsedTextures function
	 //Material->GetUsedTextures(UsedTextures, EMaterialQualityLevel::Num, true, ERHIFeatureLevel::Num, true);
  //  
		// for (UTexture* Texture : UsedTextures)
		// {
		//	 UTexture2D* Texture2D = Cast<UTexture2D>(Texture);
		//	 if (Texture2D)
		//	 {
		//		 // Use the texture as needed
		//		 FogOfWarTexture = Texture2D;
		//		 UE_LOG(LogTemp, Warning, TEXT("Fog of War Texture: %s"), FogOfWarTexture ? *FogOfWarTexture->GetName() : TEXT("None"));
		//		 break; // Exit loop after finding the first texture
		//	 }
		// }


   // if (Material)
   // {
   //     // Access the texture from the material
		 //UTexture2D* FogOfWarTexture = Cast<UTexture2D>(Material->GetTextureParameterValue(FName("FogTexture"), nullptr));
		 //UTexture2D* FogOfWarTexture = Cast<UTexture2D>(Material->GetUsedTextures(FName("FogTexture"), nullptr));
   //     
   //     if (FogOfWarTexture)
   //     {
   //         // Use the texture as needed
   //     }
   // }

	//Set size of mesh based on level floor mesh size

	}


	// Initialize the visibility grid based on
	// The fog of war texture size
	//int32 TextureSizeX = FogOfWarTexture->GetSizeX();
	//int32 TextureSizeY = FogOfWarTexture->GetSizeY();

	//VisibilityGrid.Init(TArray<bool>(), TextureSizeX);
	//for (int32 i = 0; i < VisibilityGrid.Num(); i++)
	//{
	//	VisibilityGrid[i].Init(true, TextureSizeY);
	//}
	//
	//if (FogOfWarTexture)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("TextureSizeX = %i"), TextureSizeX);
	//	UE_LOG(LogTemp, Warning, TEXT("TextureSizeY = %i"), TextureSizeY);
	//}

}

// Called every frame
void AFogOfWarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//disable temporarily
	//UpdateFogOfWarTexture();

	// Example usage
	//FVector PlayerPosition = FVector(100.0f, 100.0f, 0.0f); // Example position
	//float RevealRadius = 200.0f;
	//SetFogVisibility(PlayerPosition, RevealRadius, 0.0f); // Make the area fully transparent

}

//Not using currently
//void AFogOfWarActor::UpdateFogOfWarTexture()
//{
//	if (FogOfWarTexture)
//	{
//		// Update the fog of war texture based on the visibility grid
//		// Get the fog of war texture size
//		int32 TextureSizeX = FogOfWarTexture->GetSizeX();
//		int32 TextureSizeY = FogOfWarTexture->GetSizeY();
//		
//		// Create a dynamic texture to update the fog of war
//		TArray<FColor> TextureColors;
//		TextureColors.Init(FColor(0, 0, 0, 255), TextureSizeX * TextureSizeY);
//
//		// Iterate over each pixel in the texture
//		for (int32 Y = 0; Y < TextureSizeY; Y++)
//		{
//			for (int32 X = 0; X < TextureSizeX; X++)
//			{
//				// Calculate the index of the pixel in the texture array
//				int32 TextureIndex = Y * TextureSizeX + X;
//
//				// Check if the pixel is visible or not
//				bool bVisible = VisibilityGrid[X][Y];
//
//				// Set the color of the pixel based on visibility
//				TextureColors[TextureIndex] = bVisible ? FColor(0, 0, 0, 0) : FColor(0, 0, 0, 255);
//			}
//		}
//
//		// Update the fog of war texture
//		FUpdateTextureRegion2D UpdateRegion(0, 0, 0, 0, TextureSizeX, TextureSizeY);
//		FogOfWarTexture->UpdateTextureRegions(0, 1, &UpdateRegion, TextureSizeX * 4, 4, (uint8*)TextureColors.GetData());
//
//		// You can use Render Target or Texture2D and update it based on VisibilityGrid
//		
//	}
//}

//Not using currently:
//void AFogOfWarActor::UpdateVisibilityGrid(const FVector2D& PlayerGridPosition)
//{
//	// Clear the visibility grid
//	for (int32 Y = 0; Y < VisibilityGrid.Num(); Y++)
//	{
//		for (int32 X = 0; X < VisibilityGrid[Y].Num(); X++)
//		{
//			VisibilityGrid[X][Y] = false;
//		}
//	}
//
//	// Calculate player's field of view and update visibility grid
//	// based on the player's position and field of view
//	// Using ray casting
//
//	//float AngleStep = FieldOfViewAngle / RayCount;
//
//	// Calculate the starting angle of the field of view
//	//float StartAngle = GetActorRotation().Yaw - FieldOfViewAngle * 0.5f;
//
//	// Iterate through each ray
//	for (int32 RayIndex = 0; RayIndex < RayCount; RayIndex++)
//	{
//		// Calculate the current angle of the ray
//		float CurrentAngle = StartAngle + RayIndex * AngleStep;
//
//		// Convert the angle to a direction vector
//		FVector RayDirection = FRotationMatrix(FRotator(0, CurrentAngle, 0)).GetScaledAxis(EAxis::X);
//
//		// Perform ray tracing to check visibility
//		FHitResult HitResult;
//		FVector RayStart = FVector(PlayerGridPosition.X, PlayerGridPosition.Y, GetActorLocation().Z);
//		FVector RayEnd = RayStart + RayDirection * 1000.0f; // Adjust 1000.0f as needed for your game world size
//
//		FCollisionQueryParams CollisionParams;
//		CollisionParams.AddIgnoredActor(this);
//
//		if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, ECC_Visibility, CollisionParams))
//		{
//			// Hit something, mark as visible
//			int32 HitX = FMath::FloorToInt(HitResult.ImpactPoint.X);
//			int32 HitY = FMath::FloorToInt(HitResult.ImpactPoint.Y);
//			VisibilityGrid[HitX][HitY] = true;
//		}
//	}
//
//}

void AFogOfWarActor::UpdateMeshSize(const FVector& FloorSize)
{
	
	FogSize = FloorSize + FogHeight;

	FogOfWarMesh->SetWorldScale3D(FogSize);
	//FogOfWarMesh->SetRelativeScale3D(FloorSize);

	UE_LOG(LogTemp, Warning, TEXT("FogSize = %s"), *FogSize.ToString());

}

void AFogOfWarActor::SetFogVisibility(FVector Position, FVector Direction, float FieldOfViewAngle, float VisionRange, float Opacity)
{
	if (DynamicMaterialInstance)
	{
		DynamicMaterialInstance->SetVectorParameterValue(TEXT("Position"), Position);
		DynamicMaterialInstance->SetVectorParameterValue(TEXT("Direction"), Direction);
		DynamicMaterialInstance->SetScalarParameterValue(TEXT("FieldOfViewAngle"), FieldOfViewAngle);
		DynamicMaterialInstance->SetScalarParameterValue(TEXT("VisionRange"), VisionRange);
		DynamicMaterialInstance->SetScalarParameterValue(TEXT("Opacity"), Opacity);
	}
}
