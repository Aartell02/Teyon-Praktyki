// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PRAKTYKI_API AVehicleBase : public APawn
{
	GENERATED_BODY()

public:
	AVehicleBase();

	virtual void Tick(float DeltaTime) override;

    void Throttle(float Value);
    void Steer(float Value);
    void ReleaseHandbrake();
    void ActivateHandbrake();
    void SwitchCamera();
    void UpdateSteeringWheel(float DeltaTime);
    void ApplyFriction();
    void ApplyBrakeForce();
    void SetBrake(float DeltaTime);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* ChaseCamera;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CockpitCamera;

    UCameraComponent* ActiveCamera;

    FVector MovementInput;
    float TurnInput;

    float SteeringAngleSpeed = 90.0f;
    float CurrentSteeringAngle = 0.f;

    UPROPERTY(BlueprintReadWrite)
    bool bInputBlocked = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float ThrottleForceStrength = 600000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float SteeringTorqueStrength = 350000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float FrontAxleOffset = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float DriftFactor = 0.1f;

    UPROPERTY(EditAnywhere, Category = "Movement|Drift")
    float DriftRecoverSpeed = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float BrakeInput = 0.8f;  

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Physics")
    float BrakeForce = 500000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    bool bHandbrake = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    USkeletalMeshComponent* Chassis;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Main_Body;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Seat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Interior;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Window;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Cockpit_Console;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Engine_Components;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Net;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Pedal_Brake;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Pedal_Acceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Steering_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* FL_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* FR_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* BL_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* BR_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* FL_Brake_Disc;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* FR_Brake_Disc;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* BL_Brake_Disc;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* BR_Brake_Disc;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* R_Boot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* F_Bumper;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* R_Bumper;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* B_Diffuser;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* L_Door;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* R_Door;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* L_Fender;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* R_Fender;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* F_Hood;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* B_Spoiler;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* L_Wing_Mirror;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* R_Wing_Mirror;

protected:
        virtual void BeginPlay() override;

};
