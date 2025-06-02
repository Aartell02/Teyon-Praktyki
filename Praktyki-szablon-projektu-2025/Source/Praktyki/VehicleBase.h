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
	// Sets default values for this pawn's properties
	AVehicleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    float CurrentSteeringAngle = 0.0f; // in degrees

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // Input handlers
    void Throttle(float Value);
    void Steer(float Value);
    void ApplyFriction();
    void ApplyBrakeForce();
    void ReleaseHandbrake();
    void ActivateHandbrake();
    void SetBrake(float DeltaTime);

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCameraComponent* Camera;

    // Input
    FVector MovementInput;
    float TurnInput;
    float SteeringAngle = 0.0f;
    float MaxSteeringAngle = 30.0f;
    float SteeringReturnSpeed = 150.0f;

    // Parametry fizyki
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float ThrottleForceStrength = 400000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float SteeringTorqueStrength = 1000000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    float FrontAxleOffset = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float DriftFactor = 0.05f;

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle|Wheels")
    USceneComponent* FL_Wheel_Turn;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle|Wheels")
    USceneComponent* FR_Wheel_Turn;

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

};
