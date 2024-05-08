// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TopDownFOWCharacter.h"
#include "../FogOfWarActor.h"
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
   void UpdateVisibilityGrid();

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog of War")
   
   TSubclassOf<AFogOfWarActor> FogOfWarActorClass;
   
   // Fog of War actor
   UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
   
   AFogOfWarActor* FogOfWarActor;

   FVector2D LastPlayerGridPosition;

   //test change for git

};
