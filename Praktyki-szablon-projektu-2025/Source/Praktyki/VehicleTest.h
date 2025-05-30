// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleTest.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PRAKTYKI_API AVehicleTest : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicleTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    // Input handlers
    void Throttle(float Value);
    void Steer(float Value);
    void ApplyFriction(float DeltaTime);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCameraComponent* Camera;

    // Input
    FVector MovementInput;
    float TurnInput;

    // Parametry fizyki
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float ThrottleForceStrength = 800000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float SteeringTorqueStrength = 1800000.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle|Movement")
    float DriftFactor =0.9f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    USkeletalMeshComponent* Chassis;

};
