// Copyright 2025 Teyon. All Rights Reserved.

#include "VehicleBase.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Logging/LogMacros.h"
#include "Camera/CameraComponent.h"

AVehicleBase::AVehicleBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Chassis root enable physics
    Chassis = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chassis"));
    check(Chassis);
    SetRootComponent(Chassis);
    Chassis->SetSimulatePhysics(true);

    // Bone merge
    Main_Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main_Body"));
    Main_Body->SetupAttachment(Chassis, TEXT("Body"));

    FL_Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FL_Wheel"));
    FL_Wheel->SetupAttachment(Chassis, TEXT("wheel_front_left_spin"));

    FR_Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FR_Wheel"));
    FR_Wheel->SetupAttachment(Chassis, TEXT("wheel_front_right_spin"));

    BL_Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BL_Wheel"));
    BL_Wheel->SetupAttachment(Chassis, TEXT("wheel_back_left_spin"));

    BR_Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BR_Wheel"));
    BR_Wheel->SetupAttachment(Chassis, TEXT("wheel_back_right_spin"));

    R_Boot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Boot"));
    R_Boot->SetupAttachment(Chassis, TEXT("boot_rear"));

    F_Bumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("F_Bumper"));
    F_Bumper->SetupAttachment(Chassis, TEXT("bumper_front"));

    R_Bumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Bumper"));
    R_Bumper->SetupAttachment(Chassis, TEXT("bumper_rear"));

    B_Diffuser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("B_Diffuser"));
    B_Diffuser->SetupAttachment(Chassis, TEXT("diffuser_back"));

    L_Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_Door"));
    L_Door->SetupAttachment(Chassis, TEXT("door_left"));

    R_Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Door"));
    R_Door->SetupAttachment(Chassis, TEXT("door_right"));

    L_Fender = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_Fender"));
    L_Fender->SetupAttachment(Chassis, TEXT("fender_left"));

    R_Fender = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Fender"));
    R_Fender->SetupAttachment(Chassis, TEXT("fender_right"));

    F_Hood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("F_Hood"));
    F_Hood->SetupAttachment(Chassis, TEXT("hood_front"));

    B_Spoiler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("B_Spoiler"));
    B_Spoiler->SetupAttachment(Chassis, TEXT("spoiler_back"));

    L_Wing_Mirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_Wing_Mirror"));
    L_Wing_Mirror->SetupAttachment(Chassis, TEXT("window_left"));

    R_Wing_Mirror = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Wing_Mirror"));
    R_Wing_Mirror->SetupAttachment(Chassis, TEXT("window_right"));
    
    // Mesh load
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChassisMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SK_Porsche_911_GT3-R.SK_Porsche_911_GT3-R"));
    if (ChassisMeshAsset.Succeeded())
    {
        Chassis->SetSkeletalMesh(ChassisMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Chassis skeletal mesh loaded successfully"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load chassis skeletal mesh"));
    }
    static ConstructorHelpers::FObjectFinder<UStaticMesh> FrontWheelMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Wheel.SM_Porsche_911_GT3_R_Front_Wheel"));
    if (FrontWheelMeshAsset.Succeeded())
    {
        UE_LOG(LogTemp, Log, TEXT("front wheel load success"));
        FL_Wheel->SetStaticMesh(FrontWheelMeshAsset.Object);
        FR_Wheel->SetStaticMesh(FrontWheelMeshAsset.Object);
    }
    else UE_LOG(LogTemp, Log, TEXT("front wheel load error"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> RearWheelMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Wheel.SM_Porsche_911_GT3_R_Rear_Wheel"));
    if (RearWheelMeshAsset.Succeeded())
    {
        UE_LOG(LogTemp, Log, TEXT("rear wheel load success"));
        BL_Wheel->SetStaticMesh(RearWheelMeshAsset.Object);
        BR_Wheel->SetStaticMesh(RearWheelMeshAsset.Object);
    }
    else UE_LOG(LogTemp, Log, TEXT("rear wheel load error"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MainBodyMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Main_Body.SM_Porsche_911_GT3_R_Main_Body"));

    if (MainBodyMeshAsset.Succeeded())
    {
        Main_Body->SetStaticMesh(MainBodyMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Main body mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load main body mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> RearBootMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Boot.SM_Porsche_911_GT3_R_Rear_Boot"));
    if (RearBootMeshAsset.Succeeded())
    {
        R_Boot->SetStaticMesh(RearBootMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Rear boot mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load rear boot mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> FrontBumperMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Bumper.SM_Porsche_911_GT3_R_Front_Bumper"));
    if (FrontBumperMeshAsset.Succeeded())
    {
        F_Bumper->SetStaticMesh(FrontBumperMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Front bumper mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load front bumper mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> RearBumperMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Bumper.SM_Porsche_911_GT3_R_Rear_Bumper"));
    if (RearBumperMeshAsset.Succeeded())
    {
        R_Bumper->SetStaticMesh(RearBumperMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Rear bumper mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load rear bumper mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DiffuserMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Diffuser.SM_Porsche_911_GT3_R_Rear_Diffuser"));
    if (DiffuserMeshAsset.Succeeded())
    {
        B_Diffuser->SetStaticMesh(DiffuserMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Diffuser mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load diffuser mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorLeftMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Door_Left.SM_Porsche_911_GT3_R_Door_Left"));
    if (DoorLeftMeshAsset.Succeeded())
    {
        L_Door->SetStaticMesh(DoorLeftMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Left door mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load left door mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorRightMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Door_Right.SM_Porsche_911_GT3_R_Door_Right"));
    if (DoorRightMeshAsset.Succeeded())
    {
        R_Door->SetStaticMesh(DoorRightMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Right door mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load right door mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> FenderLeftMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Fender_Left.SM_Porsche_911_GT3_R_Fender_Left"));
    if (FenderLeftMeshAsset.Succeeded())
    {
        L_Fender->SetStaticMesh(FenderLeftMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Left fender mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load left fender mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> FenderRightMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Fender_Right.SM_Porsche_911_GT3_R_Fender_Right"));
    if (FenderRightMeshAsset.Succeeded())
    {
        R_Fender->SetStaticMesh(FenderRightMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Right fender mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load right fender mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> HoodFrontMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Hood.SM_Porsche_911_GT3_R_Front_Hood"));
    if (HoodFrontMeshAsset.Succeeded())
    {
        F_Hood->SetStaticMesh(HoodFrontMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Front hood mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load front hood mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SpoilerBackMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Spoiler.SM_Porsche_911_GT3_R_Rear_Spoiler"));
    if (SpoilerBackMeshAsset.Succeeded())
    {
        B_Spoiler->SetStaticMesh(SpoilerBackMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Spoiler mesh loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load spoiler mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MirrorMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Wing_Mirror_Left.SM_Porsche_911_GT3_R_Wing_Mirror_Left"));
    if (MirrorMeshAsset.Succeeded())
    {
        L_Wing_Mirror->SetStaticMesh(MirrorMeshAsset.Object);
        R_Wing_Mirror->SetStaticMesh(MirrorMeshAsset.Object);
        UE_LOG(LogTemp, Log, TEXT("Mirror meshes loaded successfully"));
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to load mirror mesh"));

    // === Mesh load end ===

    /*
    static ConstructorHelpers::FObjectFinder<UStaticMesh> RearBootMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Boot.SM_Porsche_911_GT3_R_Rear_Boot"));
    if (RearBootMeshAsset.Succeeded())
    {
        UE_LOG(LogTemp, Log, TEXT("rear boot load success"));
        R_Boot->SetStaticMesh(RearBootMeshAsset.Object);
    }
    else UE_LOG(LogTemp, Log, TEXT("rear boot load error"));
    */

    
    MovementInput = FVector::ZeroVector;
    TurnInput = 0.f;
    SteeringAngle = 0.f;
    WheelSpinAngle = 0.f;
}

void AVehicleBase::BeginPlay()
{
    Super::BeginPlay();
}

void AVehicleBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!MovementInput.IsNearlyZero())
    {
        FVector Force = Chassis->GetForwardVector() * MovementInput.X * 100000.f;
        Chassis->AddForce(Force);
    }

    if (FMath::Abs(TurnInput) > 0.1f)
    {
        FVector Torque = FVector(0.f, 0.f, 1.f) * TurnInput * 100000.f;
        Chassis->AddTorqueInRadians(Torque);
    }

    SteeringAngle = TurnInput * 30.f;
    WheelSpinAngle += MovementInput.X * DeltaTime * 500.f;
}

void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AVehicleBase::MoveForward);
    PlayerInputComponent->BindAxis("TurnRight", this, &AVehicleBase::TurnRight);
}

void AVehicleBase::MoveForward(float Value)
{
    MovementInput.X = FMath::Clamp(Value, -1.f, 1.f);
}

void AVehicleBase::TurnRight(float Value)
{
    TurnInput = FMath::Clamp(Value, -1.f, 1.f);
}
