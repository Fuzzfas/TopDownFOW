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

AFogOfWarActor::~AFogOfWarActor()
{
	// Cleanup memory
	delete[] LowResData;
	delete[] HighResData;
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

void AFogOfWarActor::DrawDebugConeFOW(FVector2D UnitPosition, FVector2D UnitDirection, float ConeAngle, float VisionRange)
{
	FVector UnitPosition3D(UnitPosition, 0);
	FVector UnitDirection3D(UnitDirection, 0);
	float HalfConeAngle = FMath::DegreesToRadians(ConeAngle / 2);

	DrawDebugCone(GetWorld(), UnitPosition3D, UnitDirection3D, VisionRange, HalfConeAngle, HalfConeAngle, 12, FColor::Green, false, -1, 0, 5);
	
	
}

bool AFogOfWarActor::IsWithinCone(FVector2D Position, FVector2D UnitPosition, FVector2D UnitDirection, float ConeAngle, float RevealRadius)
{
	FVector2D ToPixel = Position - UnitPosition;
	float Distance = ToPixel.Size();

	// Print debug information
	UE_LOG(LogTemp, Warning, TEXT("Position: %s, UnitPosition: %s, ToPixel: %s, Distance: %f"),
		*Position.ToString(), *UnitPosition.ToString(), *ToPixel.ToString(), Distance);

	// Check if the pixel is within the reveal radius
	if (Distance > RevealRadius)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pixel is outside the reveal radius"));
		return false;
	}

	// Normalize the direction vectors
	ToPixel.Normalize();
	UnitDirection.Normalize();

	// Compute the angle between the unit's direction and the pixel's direction
	float CosTheta = FVector2D::DotProduct(ToPixel, UnitDirection);
	float Theta = FMath::Acos(CosTheta);

	// Print debug information
	UE_LOG(LogTemp, Warning, TEXT("CosTheta: %f, Theta: %f (in radians), Theta: %f (in degrees), HalfConeAngle: %f (in radians)"),
		CosTheta, Theta, FMath::RadiansToDegrees(Theta), FMath::DegreesToRadians(ConeAngle / 2));

	// Convert the cone angle to radians
	float HalfConeAngle = FMath::DegreesToRadians(ConeAngle / 2);

	// Check if the pixel is within the cone angle
	bool IsWithin = Theta <= HalfConeAngle;
	if (IsWithin)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pixel is within the cone"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pixel is outside the cone"));
	}

	return IsWithin;
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
		//DynamicMaterialInstance->SetStaticSwitchParameterValue(FName("YourStaticSwitchParameterName"), bIsVisible, true);

	}
}

void AFogOfWarActor::InitializeRevealedTexture()
{
	int WorldScaleFactor = 100;

	FVector FogWorldSize = FogOfWarMesh->GetRelativeScale3D() * WorldScaleFactor;
	HighResTextureSizeX = FogWorldSize.X;
	HighResTextureSizeY = FogWorldSize.Y;

	LowResTextureSizeX = HighResTextureSizeX/10;
	LowResTextureSizeY = HighResTextureSizeY/10;

	// Allocate memory
	LowResData = new FColor[LowResTextureSizeX * LowResTextureSizeY];
	HighResData = new FColor[HighResTextureSizeX * HighResTextureSizeY];

	PreviouslyRevealedTexture = UTexture2D::CreateTransient(LowResTextureSizeX, LowResTextureSizeY, PF_B8G8R8A8); //PF_B8G8R8A8: The pixel format, where each pixel is represented by four 8-bit channels (Blue, Green, Red, Alpha)
	PreviouslyRevealedTexture->CompressionSettings = TC_VectorDisplacementmap; //used to ensure the texture retains high fidelity for each pixel's color data, which is important for precise visibility tracking in the fog of war system.
	PreviouslyRevealedTexture->SRGB = false; //This line disables sRGB (standard RGB) encoding for the texture. sRGB encoding is used to adjust colors for display on standard monitors. Disabling it is important here because we need the raw, linear color values for accurate fog of war calculations, rather than values adjusted for display purposes.
	PreviouslyRevealedTexture->AddToRoot(); // This line adds the texture to the root set, preventing it from being garbage collected.In Unreal Engine, objects that are not referenced anywhere can be automatically deleted by the garbage collector.Adding the texture to the root ensures it remains in memory as long as it's needed, even if there are no other references to it.
	PreviouslyRevealedTexture->UpdateResource(); //This line updates the texture resource, making sure any changes made to the texture's properties are applied. This is necessary after modifying texture properties like compression settings or sRGB encoding to ensure these changes take effect.

	// Initialize the LowResData with white
	FMemory::Memset(LowResData, 255, LowResTextureSizeX * LowResTextureSizeY * sizeof(FColor));
	// Initialize the HighResData with white
	FMemory::Memset(HighResData, 255, HighResTextureSizeX * HighResTextureSizeY * sizeof(FColor));



	FTexture2DMipMap& Mip = PreviouslyRevealedTexture->GetPlatformData()->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memset(Data, 255, LowResTextureSizeX * LowResTextureSizeY * sizeof(FColor)); //Fills entire memory block in a single call, more efficient (255 means white in RGBA)



	// Fill the texture with white pixels (old, less efficient method for my purposes)
	//FColor* FormattedImageData = static_cast<FColor*>(Data);
	//FColor WhiteColor = FColor::White;

	//for (int32 y = 0; y < TextureSizeY; y++)
	//{
	//	for (int32 x = 0; x < TextureSizeX; x++)
	//	{
	//		FormattedImageData[y * TextureSizeX + x] = WhiteColor;
	//	}
	//}


	Mip.BulkData.Unlock();
	PreviouslyRevealedTexture->UpdateResource();

}

void AFogOfWarActor::UpdatePreviouslyRevealedTexture(FVector Position, FVector Direction, float FieldOfViewAngle, float VisionRange, float Opacity)
{
	if (!PreviouslyRevealedTexture)
	{
		UE_LOG(LogTemp, Warning, TEXT("PreviouslyRevealedTexture is null"));
		return;
	}

	FTexturePlatformData* PlatformData = PreviouslyRevealedTexture->GetPlatformData();
	if (!PlatformData)
	{
		UE_LOG(LogTemp, Warning, TEXT("PreviouslyRevealedTexture->GetPlatformData() is null"));
		return;
	}

	int WorldToTextureScale = 1;

	// Access the first mip level
	FTexture2DMipMap& Mip = PlatformData->Mips[0];

	// Lock the texture for writing, provides direct access to the texture’s memory, allowing safe modifications.
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);

	// Convert the unit position to texture coordinates
	int32 CenterX = Position.X * WorldToTextureScale;
	int32 CenterY = Position.Y * WorldToTextureScale;
	FVector2D UnitPos2D(CenterX, CenterY);
	FVector2D UnitDir2D(Direction.X, Direction.Y);

	HighResTextureSizeX = PreviouslyRevealedTexture->GetSizeX();
	HighResTextureSizeY = PreviouslyRevealedTexture->GetSizeY();

	// Update the texture within the reveal radius and cone angle (low res version)
	for (int32 Y = 0; Y < LowResTextureSizeY; ++Y)
	{
		for (int32 X = 0; X < LowResTextureSizeX; ++X)
		{
			FVector2D PixelPos(X, Y);

			if (IsWithinCone(PixelPos, UnitPos2D, UnitDir2D, FieldOfViewAngle, VisionRange))
			{
				FColor& Pixel = ((FColor*)Data)[Y * LowResTextureSizeX + X];
				Pixel = FColor::Black;  // Mark as revealed (black = 0 for extinction value)

				if (GEngine)
				{
					// Create the full message string
					FString Message = FString::Printf(TEXT("Marked Position as revealed..."));
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
				}
			}
		}
	}

	//Upscaling

	int32 ScaleFactorX = HighResTextureSizeX / LowResTextureSizeX;
	int32 ScaleFactorY = HighResTextureSizeY / LowResTextureSizeY;

	for (int32 Y = 0; Y < LowResTextureSizeY; ++Y)
	{
		for (int32 X = 0; X < LowResTextureSizeX; ++X)
		{
			FColor& LowResPixel = ((FColor*)LowResData)[Y * LowResTextureSizeX + X];

			// Copy the low-resolution pixel into a block of the high-resolution texture
			for (int32 OffsetY = 0; OffsetY < ScaleFactorY; ++OffsetY)
			{
				for (int32 OffsetX = 0; OffsetX < ScaleFactorX; ++OffsetX)
				{
					int32 HighResX = X * ScaleFactorX + OffsetX;
					int32 HighResY = Y * ScaleFactorY + OffsetY;

					FColor& HighResPixel = ((FColor*)HighResData)[HighResY * HighResTextureSizeX + HighResX];
					HighResPixel = LowResPixel;
				}
			}
		}
	}


	// Unlock and update the texture (ensures engine can safely use the modified data)
	Mip.BulkData.Unlock();
	PreviouslyRevealedTexture->UpdateResource();
}

