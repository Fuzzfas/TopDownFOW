// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TopDownFOWCharacter.h"
#include "../FogOfWarActor.h"
#include "LevelFloorActor.h"
//#include "../../../Game/TopDown/Blueprints/BP_FOWActor.h"
#include "SubTopDownFOWCharacter.generated.h"

// Forward declaration
//class ABP_FOWActor;

/**
 * 
 */
UCLASS(Blueprintable)
class TOPDOWNFOW_API ASubTopDownFOWCharacter : public ATopDownFOWCharacter
{
	GENERATED_BODY()

public:
   ASubTopDownFOWCharacter();
   
   virtual void Tick(float DeltaTime) override;
	

protected:
   

   FVector2D GetPlayerGridPosition();
   //void UpdateVisibilityGrid();
   virtual void PostInitProperties() override; //earliest that we can spawn the FogOfWarActor

   // Called when the game starts or when spawned
   virtual void BeginPlay() override;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
   
   TSubclassOf<AFogOfWarActor> FogOfWarActorClass;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
   TSubclassOf<ALevelFloorActor> LevelFloorActorClass;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
   float RevealRadius = 200.0f;
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
   float FieldOfViewAngle = 90.0f; // FOV in degrees
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
   float VisionRange = 800.0f;
   
   // Fog of War actor
   UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
   
   AFogOfWarActor* FogOfWarActor = nullptr;
   ALevelFloorActor* LevelFloorActor = nullptr;

   FVector2D LastPlayerGridPosition;
   FVector LastPlayerDirection;
   
   //For reducing loop frequency of UpdatePreviouslyRevealedTexture() in FogOfWarActor;
   float TimeSinceLastUpdate = 0.0f;
   const float UpdateInterval = 0.5f; // Update every 0.5 seconds


};
