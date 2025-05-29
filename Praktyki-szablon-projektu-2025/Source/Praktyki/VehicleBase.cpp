// Copyright 2025 Teyon. All Rights Reserved.

#include "VehicleBase.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Logging/LogMacros.h"


AVehicleBase::AVehicleBase()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    Chassis = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chassis"));
    // Mesh load
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> ChassisMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SK_Porsche_911_GT3-R.SK_Porsche_911_GT3-R"));
    if (ChassisMeshAsset.Succeeded()) Chassis->SetSkeletalMesh(ChassisMeshAsset.Object);

    // Load physics asset
    static UPhysicsAsset* PhysicsAsset = LoadObject<UPhysicsAsset>(nullptr, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SK_Porsche_911_GT3-R_PhysicsAsset.SK_Porsche_911_GT3-R_PhysicsAsset"));
    if (PhysicsAsset) Chassis->SetPhysicsAsset(PhysicsAsset);
    SetRootComponent(Chassis);
    UPhysicsAsset* LoadedPhysicsAsset = LoadObject<UPhysicsAsset>(nullptr, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SK_Porsche_911_GT3-R_PhysicsAsset.SK_Porsche_911_GT3-R_PhysicsAsset"));
    Chassis->SetPhysicsAsset(LoadedPhysicsAsset);

    if (Chassis->IsSimulatingPhysics())
    {
        UE_LOG(LogTemp, Warning, TEXT("Simulating physics is enabled."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Simulating physics is NOT enabled."));
    }
    
    // Spring arm (ramiê kamery)
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Chassis);
    SpringArm->SocketOffset = FVector(0.f, 0.f, 200.f);
    SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f)); 
    SpringArm->TargetArmLength = 350.0f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 5.0f;
    SpringArm->bUsePawnControlRotation = true;

    // Kamera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;
    // Bone merge
    //SK_Porsche_911_Gt3_R1
#define CREATE_AND_ATTACH(name, socket) \
    name = CreateDefaultSubobject<UStaticMeshComponent>(TEXT(#name)); \
    name->AttachToComponent(Chassis, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT(socket));
    // Grouped car components
    CREATE_AND_ATTACH(Main_Body, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Seat, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Interior, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Window, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Cockpit_Console, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Engine_Components, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Net, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Pedal_Brake, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Pedal_Acceleration, "SK_Porsche_911_Gt3_R1")
    CREATE_AND_ATTACH(Steering_Wheel, "SK_Porsche_911_Gt3_R1")

    CREATE_AND_ATTACH(FL_Wheel, "wheel_front_left_spin")
    CREATE_AND_ATTACH(FR_Wheel, "wheel_front_right_spin")
    CREATE_AND_ATTACH(BL_Wheel, "wheel_back_left_spin")
    CREATE_AND_ATTACH(BR_Wheel, "wheel_back_right_spin")

    CREATE_AND_ATTACH(FL_Brake_Disc, "wheel_front_left_spin")
    CREATE_AND_ATTACH(FR_Brake_Disc, "wheel_front_right_spin")
    CREATE_AND_ATTACH(BL_Brake_Disc, "wheel_back_left_spin")
    CREATE_AND_ATTACH(BR_Brake_Disc, "wheel_back_right_spin")

    CREATE_AND_ATTACH(R_Boot, "boot_rear")
    CREATE_AND_ATTACH(F_Bumper, "bumper_front")
    CREATE_AND_ATTACH(R_Bumper, "bumper_rear")
    CREATE_AND_ATTACH(B_Diffuser, "diffuser_back")

    CREATE_AND_ATTACH(L_Door, "door_left")
    CREATE_AND_ATTACH(R_Door, "door_right")

    CREATE_AND_ATTACH(L_Fender, "fender_left")
    CREATE_AND_ATTACH(R_Fender, "fender_right")

    CREATE_AND_ATTACH(F_Hood, "hood_front")
    CREATE_AND_ATTACH(B_Spoiler, "spoiler_back")

    CREATE_AND_ATTACH(L_Wing_Mirror, "wing_mirror_left")
    CREATE_AND_ATTACH(R_Wing_Mirror, "wing_mirror_right")

#undef CREATE_AND_ATTACH
   

    auto LoadMesh = [](UStaticMeshComponent* Comp, const TCHAR* Path)
        {
            ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(Path);
            if (MeshAsset.Succeeded())
                Comp->SetStaticMesh(MeshAsset.Object);
        };

    LoadMesh(Main_Body, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Main_Body.SM_Porsche_911_GT3_R_Main_Body"));
    LoadMesh(Seat, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Seat_Net_Clamps.SM_Porsche_911_GT3_R_Seat_Net_Clamps"));
    Seat->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LoadMesh(Interior, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Interior.SM_Porsche_911_GT3_R_Interior"));
    Interior->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    LoadMesh(Window, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Exterior_Interior_Windows.SM_Porsche_911_GT3_R_Exterior_Interior_Windows"));
    LoadMesh(Cockpit_Console, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Cockpit_Console.SM_Porsche_911_GT3_R_Cockpit_Console"));
    LoadMesh(Engine_Components, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Engine_Components.SM_Porsche_911_GT3_R_Engine_Components"));
    LoadMesh(Net, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Net.SM_Porsche_911_GT3_R_Net"));
    LoadMesh(Pedal_Brake, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Pedal_Brake.SM_Porsche_911_GT3_R_Pedal_Brake"));
    Pedal_Brake->AttachToComponent(Interior, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Pedal_brake");
    LoadMesh(Pedal_Acceleration, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Pedal_Acceleration.SM_Porsche_911_GT3_R_Pedal_Acceleration"));
    Pedal_Acceleration->AttachToComponent(Interior, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Pedal_acceleration");
    LoadMesh(Steering_Wheel, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Steering_Wheel.SM_Porsche_911_GT3_R_Steering_Wheel"));
    Steering_Wheel->AttachToComponent(Interior, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SteeringWheel");
    LoadMesh(FL_Wheel, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Wheel.SM_Porsche_911_GT3_R_Front_Wheel"));
    LoadMesh(FR_Wheel, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Wheel.SM_Porsche_911_GT3_R_Front_Wheel"));
    FR_Wheel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    LoadMesh(BL_Wheel, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Wheel.SM_Porsche_911_GT3_R_Rear_Wheel"));
    LoadMesh(BR_Wheel, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Wheel.SM_Porsche_911_GT3_R_Rear_Wheel"));
    BR_Wheel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    LoadMesh(FL_Brake_Disc, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Brake_Disc.SM_Porsche_911_GT3_R_Front_Brake_Disc"));
    LoadMesh(FR_Brake_Disc, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Brake_Disc.SM_Porsche_911_GT3_R_Front_Brake_Disc"));
    FR_Brake_Disc->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    LoadMesh(BL_Brake_Disc, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Brake_Disc.SM_Porsche_911_GT3_R_Rear_Brake_Disc"));
    LoadMesh(BR_Brake_Disc, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Brake_Disc.SM_Porsche_911_GT3_R_Rear_Brake_Disc"));
    BR_Brake_Disc->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    LoadMesh(R_Boot, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Boot.SM_Porsche_911_GT3_R_Rear_Boot"));
    LoadMesh(F_Bumper, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Bumper.SM_Porsche_911_GT3_R_Front_Bumper"));
    LoadMesh(R_Bumper, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Bumper.SM_Porsche_911_GT3_R_Rear_Bumper"));
    LoadMesh(B_Diffuser, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Diffuser.SM_Porsche_911_GT3_R_Rear_Diffuser"));
    LoadMesh(L_Door, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Door_Left.SM_Porsche_911_GT3_R_Door_Left"));
    LoadMesh(R_Door, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Door_Right.SM_Porsche_911_GT3_R_Door_Right"));
    LoadMesh(L_Fender, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Fender_Left.SM_Porsche_911_GT3_R_Fender_Left"));
    LoadMesh(R_Fender, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Fender_Right.SM_Porsche_911_GT3_R_Fender_Right"));
    LoadMesh(F_Hood, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Hood.SM_Porsche_911_GT3_R_Front_Hood"));
    LoadMesh(B_Spoiler, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Spoiler.SM_Porsche_911_GT3_R_Rear_Spoiler"));
    LoadMesh(L_Wing_Mirror, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Wing_Mirror_Left.SM_Porsche_911_GT3_R_Wing_Mirror_Left"));
    LoadMesh(R_Wing_Mirror, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Wing_Mirror_Right.SM_Porsche_911_GT3_R_Wing_Mirror_Right"));
    // === Mesh load end ===

    MovementInput = FVector::ZeroVector;
    TurnInput = 0.f;
}

void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Throttle", this, &AVehicleBase::Throttle);
    PlayerInputComponent->BindAxis("Steer", this, &AVehicleBase::Steer);
}

void AVehicleBase::BeginPlay()
{
    Super::BeginPlay();

    Chassis->SetSimulatePhysics(true);
    Chassis->SetEnableGravity(true);
    Chassis->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Chassis->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    Chassis->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    Chassis->SetMassOverrideInKg(NAME_None, 1500.f);
    UE_LOG(LogTemp, Warning, TEXT("Chassis IsSimulatingPhysics: %s"), Chassis->IsSimulatingPhysics() ? TEXT("TRUE") : TEXT("FALSE"));
    UE_LOG(LogTemp, Warning, TEXT("Chassis Has Valid Physics Asset: %s"), Chassis->GetPhysicsAsset() ? TEXT("TRUE") : TEXT("FALSE"));

    Chassis->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
    Chassis->SetAllPhysicsAngularVelocityInRadians(FVector::ZeroVector);
}

void AVehicleBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!MovementInput.IsNearlyZero())
    {
        FVector ThrottleForce = Chassis->GetForwardVector() * MovementInput.X * ThrottleForce * DeltaTime;
        Chassis->AddForce(ThrottleForce);
    }

    if (FMath::Abs(TurnInput) > 0.1f)
    {
        FVector SteeringTorque = FVector(0.f, 0.f, 1.f) * TurnInput * SteeringTorque * DeltaTime;
        Chassis->AddTorqueInRadians(SteeringTorque);
    }
}

void AVehicleBase::Throttle(float Value)
{
    // Apply force to simulate throttle
    MovementInput.X = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AVehicleBase::Steer(float Value)
{
    // Apply torque to simulate steering
    TurnInput = FMath::Clamp(Value, -1.0f, 1.0f);
}