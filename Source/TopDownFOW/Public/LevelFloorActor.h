// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelFloorActor.generated.h"

UCLASS(Blueprintable)
class TOPDOWNFOW_API ALevelFloorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelFloorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	
	virtual void Tick(float DeltaTime) override; // Called every frame
	virtual void PostInitProperties() override;
	const FVector GetMeshSize() const;


protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")

	class UStaticMeshComponent* LevelFloorMesh;
	FVector FloorSize;
	
		

};
