// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TopDownFOWCharacter.h"
#include "Public/SubTopDownFOWCharacter.h"

#include "TopDownFOWGameMode.generated.h"

UCLASS(minimalapi)
class ATopDownFOWGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATopDownFOWGameMode();

//	void InitGameState() override;
//
//private:
//	UPROPERTY(EditAnywhere, NoClear)
//	TSubclassOf<ATopDownFOWCharacter> CustomFOWCharacter = ASubTopDownFOWCharacter::StaticClass();

};



