// Fill out your copyright notice in the Description page of Project Settings.


#include "SubTopDownFOWCharacter.h"
#include "../TopDownFOWCharacter.h"
#include "../FogOfWarActor.h"
//#include "../../../Game/TopDown/Blueprints/BP_FOWActor.h"



ASubTopDownFOWCharacter::ASubTopDownFOWCharacter()
{
   
   LastPlayerGridPosition = FVector2D::ZeroVector;
   
   if (GEngine)
   {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Custom Character spawned"));
   }

   // Log the class reference
   UE_LOG(LogTemp, Warning, TEXT("Fog of War Actor class: %s"), FogOfWarActorClass ? *FogOfWarActorClass->GetName() : TEXT("None"));


   if (IsValid(FogOfWarActorClass))
   {
      FogOfWarActor = Cast<AFogOfWarActor>(GetWorld()->SpawnActor(FogOfWarActorClass));

      //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BP_FOWActor spawned"));

      if (!FogOfWarActor)
      {
         UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Fog of War Actor"));
      }
   }

   else
   {
      UE_LOG(LogTemp, Warning, TEXT("Fog of War Actor class is not set in the editor"));
   }
   // Spawn and assign a FogOfWarActor
   //FogOfWarActorClass = AFogOfWarActor::StaticClass();  

}

void ASubTopDownFOWCharacter::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

   // Check if the player has moved to a new grid position
   FVector2D CurrentPlayerGridPosition = GetPlayerGridPosition();
   if (CurrentPlayerGridPosition != LastPlayerGridPosition)
   {
      UpdateVisibilityGrid();
      LastPlayerGridPosition = CurrentPlayerGridPosition;
   }

}

FVector2D ASubTopDownFOWCharacter::GetPlayerGridPosition()
{
   FVector PlayerLocation = GetActorLocation();
   // Convert the player's world position to grid position
   int32 GridX = FMath::FloorToInt(PlayerLocation.X / 100);
   int32 GridY = FMath::FloorToInt(PlayerLocation.Y / 100);
   return FVector2D(GridX, GridY);
}

void ASubTopDownFOWCharacter::UpdateVisibilityGrid()
{
   if (FogOfWarActor)
   {
      FVector2D PlayerGridPosition = GetPlayerGridPosition();
      // Update the visibility grid based on the player's position and field of view
      // You need to implement this function in the FogOfWarActor class
      FogOfWarActor->UpdateVisibilityGrid(PlayerGridPosition);
   }
}