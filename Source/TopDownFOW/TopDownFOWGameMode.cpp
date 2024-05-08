// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownFOWGameMode.h"
#include "TopDownFOWPlayerController.h"
#include "TopDownFOWCharacter.h"
#include "Public/SubTopDownFOWCharacter.h"
#include "GameFramework/DefaultPawn.h"
#include "UObject/ConstructorHelpers.h"

ATopDownFOWGameMode::ATopDownFOWGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownFOWPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/CustomBP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	///Script/CoreUObject.Class'/Script/TopDownFOW.SubTopDownFOWCharacter'
	//G:/Documents/Game and Programming Projects/Unreal Projects/TopDownFOW/Source/TopDownFOW/Public/SubTopDownFOWCharacter.h

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

//void ATopDownFOWGameMode::InitGameState()
//{
//	Super::InitGameState();
//
//
//	//check if no hard override is active
//	if (defaultpawnclass == adefaultpawn::staticclass())
//	{
//		//update to custom implementation
//		defaultpawnclass = customfowcharacter;
//
//
//	}
//
//	
//}