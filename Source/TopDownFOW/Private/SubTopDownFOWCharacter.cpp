// Fill out your copyright notice in the Description page of Project Settings.


#include "SubTopDownFOWCharacter.h"
#include "../TopDownFOWCharacter.h"
#include "../FogOfWarActor.h"
#include "Kismet/GameplayStatics.h"
//#include "../../../Game/TopDown/Blueprints/BP_FOWActor.h"



ASubTopDownFOWCharacter::ASubTopDownFOWCharacter()
{
   
   LastPlayerGridPosition = FVector2D::ZeroVector;
   LastPlayerDirection = FVector::ZeroVector;
   
   if (GEngine)
   {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Custom Character spawned"));
   }

   // Log the class reference
   UE_LOG(LogTemp, Warning, TEXT("Fog of War Actor class: %s"), FogOfWarActorClass ? *FogOfWarActorClass->GetName() : TEXT("None"));



   // Spawn and assign a FogOfWarActor
   //FogOfWarActorClass = AFogOfWarActor::StaticClass();  

}

void ASubTopDownFOWCharacter::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

   // Check if the player has moved to a new grid position
   FVector2D CurrentPlayerGridPosition = GetPlayerGridPosition();
   FVector CurrentPlayer3DPosition = GetActorLocation();
   FVector CurrentPlayerDirection = GetActorForwardVector();
   

   if (CurrentPlayerGridPosition != LastPlayerGridPosition || CurrentPlayerDirection != LastPlayerDirection)
   {
      //disable for now
      //UpdateVisibilityGrid();
      LastPlayerGridPosition = CurrentPlayerGridPosition;
      LastPlayerDirection = CurrentPlayerDirection;

      if (GEngine)
      {
         // Convert FVector to string
         //FString VectorString = CurrentPlayerGridPosition.ToString();
         FString VectorString2 = CurrentPlayerDirection.ToString();
         FString VectorString3 = CurrentPlayer3DPosition.ToString();

         // Create the full message string
         //FString Message = FString::Printf(TEXT("PlayerGridPosition: %s"), *VectorString);
         FString Message2 = FString::Printf(TEXT("PlayerDirection: %s"), *VectorString2);
         FString Message3 = FString::Printf(TEXT("Player3DWorldPosition: %s"), *VectorString3);

         //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Message2);
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message3);
      }
      
      FogOfWarActor->SetFogVisibility(CurrentPlayer3DPosition, CurrentPlayerDirection, FieldOfViewAngle, VisionRange, 1.0f);

      //Reduce frequency of this call for performance
      TimeSinceLastUpdate += DeltaTime;
      if (TimeSinceLastUpdate >= UpdateInterval)
      {
         FString Message = FString::Printf(TEXT("Calling UpdatePreviouslyRevealedTexture()..."));
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Message);

         FogOfWarActor->UpdatePreviouslyRevealedTexture(CurrentPlayer3DPosition, CurrentPlayerDirection, FieldOfViewAngle, VisionRange, 1.0f);
         TimeSinceLastUpdate = 0.0f;
      }
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

//void ASubTopDownFOWCharacter::UpdateVisibilityGrid()
//{
//   if (FogOfWarActor)
//   {
//      FVector2D PlayerGridPosition = GetPlayerGridPosition();
//      // Update the visibility grid based on the player's position and field of view
//      // You need to implement this function in the FogOfWarActor class
//      FogOfWarActor->UpdateVisibilityGrid(PlayerGridPosition);
//   }
//}

void ASubTopDownFOWCharacter::PostInitProperties()
{
   Super::PostInitProperties();

   // Log the class reference
   UE_LOG(LogTemp, Warning, TEXT("After BeginPlay() Fog of War Actor class: %s"), FogOfWarActorClass ? *FogOfWarActorClass->GetName() : TEXT("None"));

   if (IsValid(FogOfWarActorClass))
   {
      FogOfWarActor = Cast<AFogOfWarActor>(GetWorld()->SpawnActor(FogOfWarActorClass));
      //FogOfWarActor->AddActorLocalOffset({0.0,0.0,400.0});

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

   if (IsValid(LevelFloorActorClass))
   {
      LevelFloorActor = Cast<ALevelFloorActor>(UGameplayStatics::GetActorOfClass(GetWorld(), (ALevelFloorActor::StaticClass())));

      //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BP_FOWActor spawned"));

      if (!LevelFloorActor)
      {
         UE_LOG(LogTemp, Warning, TEXT("Failed to reference Level Floor Actor"));
      }
   }

   else
   {
      UE_LOG(LogTemp, Warning, TEXT("Level Floor Actor class is not set in the editor"));
   }



}

void ASubTopDownFOWCharacter::BeginPlay()
{
   Super::BeginPlay();


   //Matches the Floor Mesh Size with the Fog Mesh Size
   if(FogOfWarActor && LevelFloorActor)
   {
      FogOfWarActor->UpdateMeshSize(LevelFloorActor->GetMeshSize());
      FogOfWarActor->InitializeRevealedTexture();
   }
   else
   {
      UE_LOG(LogTemp, Warning, TEXT("Unable to update FogOfWarActor mesh size"));
   }

}
