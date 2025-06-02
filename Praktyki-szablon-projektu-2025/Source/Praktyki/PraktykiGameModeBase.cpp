// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "VehicleHUD.h" 
#include "VehicleBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

APraktykiGameModeBase::APraktykiGameModeBase() 
{
	HUDClass = AVehicleHUD::StaticClass();
	DefaultPawnClass = AVehicleBase::StaticClass();

	
}
