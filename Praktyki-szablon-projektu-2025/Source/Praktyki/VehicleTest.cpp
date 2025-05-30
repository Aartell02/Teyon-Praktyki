// Copyright 2025 Teyon. All Rights Reserved.


#include "VehicleTest.h"

// Sets default values
AVehicleTest::AVehicleTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicleTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVehicleTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

