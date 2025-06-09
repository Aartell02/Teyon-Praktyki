// Copyright 2025 Teyon. All Rights Reserved.


#include "VehiclePlayerController.h"
#include "VehicleBase.h"

void AVehiclePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    ControlledVehicle = Cast<AVehicleBase>(GetPawn());
    UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent called"));

    InputComponent->BindAxis("Throttle", this, &AVehiclePlayerController::Throttle);
    InputComponent->BindAxis("Steer", this, &AVehiclePlayerController::Steer);
    InputComponent->BindAxis("Brake", this, &AVehiclePlayerController::Brake);
    InputComponent->BindAction("Handbrake", IE_Pressed, this, &AVehiclePlayerController::HandbrakePressed);
    InputComponent->BindAction("Handbrake", IE_Released, this, &AVehiclePlayerController::HandbrakeReleased);
    InputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AVehiclePlayerController::SwitchCamera);
}


void AVehiclePlayerController::Throttle(float Value)
{
    if (AVehicleBase* Vehicle = GetControlledVehicle())
    {
        Vehicle->Throttle(Value);
    }
}

void AVehiclePlayerController::Steer(float Value)
{
    if (AVehicleBase* Vehicle = GetControlledVehicle())
    {
        Vehicle->Steer(Value);
    }
}

void AVehiclePlayerController::Brake(float Value)
{
    if (AVehicleBase* Vehicle = GetControlledVehicle())
    {
        Vehicle->SetBrake(Value);
    }
}

void AVehiclePlayerController::HandbrakePressed()
{
    if (AVehicleBase* Vehicle = GetControlledVehicle())
    {
        Vehicle->ActivateHandbrake();
    }
}

void AVehiclePlayerController::HandbrakeReleased()
{
    if (AVehicleBase* Vehicle = GetControlledVehicle())
    {
        Vehicle->ReleaseHandbrake();
    }
}

void AVehiclePlayerController::SwitchCamera()
{
    if (AVehicleBase* Vehicle = GetControlledVehicle())
    {
        Vehicle->SwitchCamera();
    }
}
AVehicleBase* AVehiclePlayerController::GetControlledVehicle() const
{
    return Cast<AVehicleBase>(GetPawn());
}