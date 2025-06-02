// Copyright 2025 Teyon. All Rights Reserved.


#include "MenuGameModeBase.h"
#include "MainMenuHUD.h" 
#include "UObject/ConstructorHelpers.h"


AMenuGameModeBase::AMenuGameModeBase()
{
	HUDClass = AMainMenuHUD::StaticClass();
}