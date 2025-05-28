// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleBase.generated.h"


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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void TurnRight(float Value);

    UPROPERTY(BlueprintReadOnly, Category = "Vehicle")
    float SteeringAngle;

    UPROPERTY(BlueprintReadOnly, Category = "Vehicle")
    float WheelSpinAngle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    USkeletalMeshComponent* Chassis;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* Main_Body;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* FL_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* FR_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* BL_Wheel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
    UStaticMeshComponent* BR_Wheel;

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
private:

    // Prosta fizyka
    FVector MovementInput;
    float TurnInput;
};
