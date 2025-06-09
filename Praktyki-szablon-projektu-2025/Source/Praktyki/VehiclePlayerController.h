// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VehiclePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AVehiclePlayerController : public APlayerController
{
    GENERATED_BODY()
private:
    class AVehicleBase* ControlledVehicle;

protected:
    AVehicleBase* GetControlledVehicle() const;
    virtual void SetupInputComponent() override;
    void Throttle(float Value);
    void Steer(float Value);
    void Brake(float Value);
    void HandbrakePressed();
    void HandbrakeReleased();
    void SwitchCamera();

};