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
    RootComponent = Chassis;
    Chassis->SetRelativeLocation(FVector(0.f, 0.f, +100.f));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/Vehicles/Porsche_911_GT3_R/SK_Porsche_911_GT3-R.SK_Porsche_911_GT3-R"));
    if (SkeletalMeshAsset.Succeeded())
    {
        Chassis->SetSkeletalMesh(SkeletalMeshAsset.Object);
    }

    UPhysicsAsset* PhysicsAsset = LoadObject<UPhysicsAsset>(nullptr, TEXT("/Game/Vehicles/Porsche_911_GT3_R/SK_Porsche_911_GT3-R_PhysicsAsset.SK_Porsche_911_GT3-R_PhysicsAsset"));
    if (PhysicsAsset)
    {
        Chassis->SetPhysicsAsset(PhysicsAsset);
    }

    Chassis->SetEnableGravity(true);
    Chassis->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Chassis->SetCollisionObjectType(ECC_PhysicsBody);
    Chassis->SetCollisionResponseToAllChannels(ECR_Block);
    Chassis->SetMassOverrideInKg(NAME_None, 1500.f, true);
    Chassis->SetCenterOfMass(FVector(0.f, 0.f, -50.f));
    Chassis->SetLinearDamping(0.5f);
    Chassis->SetAngularDamping(0.9f);

    UE_LOG(LogTemp, Warning, TEXT("Simulating physics is %s."), Chassis->IsSimulatingPhysics() ? TEXT("enabled") : TEXT("NOT enabled"));

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Chassis);
    SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
    SpringArm->TargetArmLength = 400.0f;
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 5.0f;
    SpringArm->CameraLagMaxDistance = 100.0f;
    SpringArm->bUsePawnControlRotation = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    MovementInput = FVector::ZeroVector;
    TurnInput = 0.f;
    DriftFactor = 0.9f;

#define CREATE_AND_ATTACH(name, socket, path, root) \
    name = CreateDefaultSubobject<UStaticMeshComponent>(TEXT(#name)); \
    name->SetupAttachment(root, TEXT(socket)); \
    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset##name(path);\
    if (MeshAsset##name.Succeeded())\
    {\
        name->SetStaticMesh(MeshAsset##name.Object);\
        name->SetSimulatePhysics(false);\
        name->SetCollisionEnabled(ECollisionEnabled::NoCollision);\
        name->SetRelativeLocation(FVector::ZeroVector);\
        name->SetRelativeRotation(FRotator::ZeroRotator);\
        name->SetRelativeScale3D(FVector(1.f));\
    }\

        CREATE_AND_ATTACH(Main_Body, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Main_Body.SM_Porsche_911_GT3_R_Main_Body"), Chassis)
        CREATE_AND_ATTACH(Seat, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Seat_Net_Clamps.SM_Porsche_911_GT3_R_Seat_Net_Clamps"), Chassis)
        CREATE_AND_ATTACH(Interior, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Interior.SM_Porsche_911_GT3_R_Interior"), Chassis)
        CREATE_AND_ATTACH(Window, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Exterior_Interior_Windows.SM_Porsche_911_GT3_R_Exterior_Interior_Windows"), Chassis)
        CREATE_AND_ATTACH(Cockpit_Console, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Cockpit_Console.SM_Porsche_911_GT3_R_Cockpit_Console"), Chassis)
        CREATE_AND_ATTACH(Engine_Components, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Engine_Components.SM_Porsche_911_GT3_R_Engine_Components"), Chassis)
        CREATE_AND_ATTACH(Net, "SK_Porsche_911_Gt3_R1", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Net.SM_Porsche_911_GT3_R_Net"), Chassis)

        CREATE_AND_ATTACH(Pedal_Brake, "Pedal_brake", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Pedal_Brake.SM_Porsche_911_GT3_R_Pedal_Brake"), Interior)
        CREATE_AND_ATTACH(Pedal_Acceleration, "Pedal_acceleration", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Pedal_Acceleration.SM_Porsche_911_GT3_R_Pedal_Acceleration"), Interior)
        CREATE_AND_ATTACH(Steering_Wheel, "SteeringWheel", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Steering_Wheel.SM_Porsche_911_GT3_R_Steering_Wheel"), Interior)

        CREATE_AND_ATTACH(FL_Wheel, "wheel_front_left_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Wheel.SM_Porsche_911_GT3_R_Front_Wheel"), Chassis)
        CREATE_AND_ATTACH(FR_Wheel, "wheel_front_right_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Wheel.SM_Porsche_911_GT3_R_Front_Wheel"), Chassis)
        CREATE_AND_ATTACH(BL_Wheel, "wheel_back_left_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Wheel.SM_Porsche_911_GT3_R_Rear_Wheel"),Chassis)
        CREATE_AND_ATTACH(BR_Wheel, "wheel_back_right_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Wheel.SM_Porsche_911_GT3_R_Rear_Wheel"),Chassis)

        CREATE_AND_ATTACH(FL_Brake_Disc, "wheel_front_left_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Brake_Disc.SM_Porsche_911_GT3_R_Front_Brake_Disc"), Chassis)
        CREATE_AND_ATTACH(FR_Brake_Disc, "wheel_front_right_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Brake_Disc.SM_Porsche_911_GT3_R_Front_Brake_Disc"), Chassis)
        CREATE_AND_ATTACH(BL_Brake_Disc, "wheel_back_left_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Brake_Disc.SM_Porsche_911_GT3_R_Rear_Brake_Disc"), Chassis)
        CREATE_AND_ATTACH(BR_Brake_Disc, "wheel_back_right_spin", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Brake_Disc.SM_Porsche_911_GT3_R_Rear_Brake_Disc"), Chassis)

        CREATE_AND_ATTACH(R_Boot, "boot_rear", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Boot.SM_Porsche_911_GT3_R_Rear_Boot"), Chassis)
        CREATE_AND_ATTACH(F_Bumper, "bumper_front", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Bumper.SM_Porsche_911_GT3_R_Front_Bumper"), Chassis)
        CREATE_AND_ATTACH(R_Bumper, "bumper_rear", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Bumper.SM_Porsche_911_GT3_R_Rear_Bumper"), Chassis)
        CREATE_AND_ATTACH(B_Diffuser, "diffuser_back", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Diffuser.SM_Porsche_911_GT3_R_Rear_Diffuser"), Chassis)
        CREATE_AND_ATTACH(L_Door, "door_left", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Door_Left.SM_Porsche_911_GT3_R_Door_Left"), Chassis)
        CREATE_AND_ATTACH(R_Door, "door_right", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Door_Right.SM_Porsche_911_GT3_R_Door_Right"), Chassis)
        CREATE_AND_ATTACH(L_Fender, "fender_left", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Fender_Left.SM_Porsche_911_GT3_R_Fender_Left"), Chassis)
        CREATE_AND_ATTACH(R_Fender, "fender_right", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Fender_Right.SM_Porsche_911_GT3_R_Fender_Right"), Chassis)
        CREATE_AND_ATTACH(F_Hood, "hood_front", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Front_Hood.SM_Porsche_911_GT3_R_Front_Hood"), Chassis)
        CREATE_AND_ATTACH(B_Spoiler, "spoiler_back", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Rear_Spoiler.SM_Porsche_911_GT3_R_Rear_Spoiler"), Chassis)
        CREATE_AND_ATTACH(L_Wing_Mirror, "wing_mirror_left", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Wing_Mirror_Left.SM_Porsche_911_GT3_R_Wing_Mirror_Left"), Chassis)
        CREATE_AND_ATTACH(R_Wing_Mirror, "wing_mirror_right", TEXT("/Game/Vehicles/Porsche_911_GT3_R/SM_Porsche_911_GT3_R_Wing_Mirror_Right.SM_Porsche_911_GT3_R_Wing_Mirror_Right"), Chassis)

#undef CREATE_AND_ATTACH
    BL_Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
    FL_Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    FR_Wheel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    FR_Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BR_Wheel->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    BR_Wheel->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    FR_Brake_Disc->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
    BR_Brake_Disc->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

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
    Chassis->WakeAllRigidBodies();
    SpringArm->SetWorldRotation(Chassis->GetComponentRotation());
    UE_LOG(LogTemp, Warning, TEXT("Chassis IsSimulatingPhysics: %s"), Chassis->IsSimulatingPhysics() ? TEXT("TRUE") : TEXT("FALSE"));
    UE_LOG(LogTemp, Warning, TEXT("Chassis Has Valid Physics Asset: %s"), Chassis->GetPhysicsAsset() ? TEXT("TRUE") : TEXT("FALSE"));
}

void AVehicleBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Chassis && Chassis->IsSimulatingPhysics())
    {
        if (!FMath::IsNearlyZero(MovementInput.X))
        {
            FVector Force = Chassis->GetForwardVector() * MovementInput.X * ThrottleForceStrength;
            Chassis->AddForce(Force);
        }

        if (FMath::Abs(TurnInput) > KINDA_SMALL_NUMBER)
        {
            FVector Torque = FVector(0.f, 0.f, TurnInput * SteeringTorqueStrength);
            Chassis->AddTorqueInRadians(Torque);
        }
        ApplyFriction(DeltaTime);

    }
}

void AVehicleBase::Throttle(float Value)
{
    MovementInput.X = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AVehicleBase::Steer(float Value)
{
    TurnInput = FMath::Clamp(Value, -1.0f, 1.0f);
}
void AVehicleBase::ApplyFriction(float DeltaTime)
{
    /*
    FVector Velocity = Chassis->GetPhysicsLinearVelocity();
    float Speed = Velocity.Size();

    if (Speed < 1.0f)  // Jeœli ju¿ prawie stoi, nic nie rób
    {
        Chassis->SetPhysicsLinearVelocity(FVector::ZeroVector);
        return;
    }

    // Si³a hamowania proporcjonalna do prêdkoœci
    float FrictionCoefficient = 5000.0f;  // Dostosuj w zale¿noœci od masy/si³y
    FVector FrictionForce = -Velocity.GetSafeNormal() * FrictionCoefficient;

    Chassis->AddForce(FrictionForce);
    FVector LateralVelocity = FVector::VectorPlaneProject(
        Chassis->GetPhysicsLinearVelocity(),
        Chassis->GetForwardVector()
    );

    FVector LateralFriction = -LateralVelocity * 50.f;  // Si³a tarcia bocznego
    Chassis->AddForce(LateralFriction);*/
    FVector Velocity = Chassis->GetPhysicsLinearVelocity();

    FVector Forward = Chassis->GetForwardVector();
    FVector Right = Chassis->GetRightVector();

    FVector LateralVelocity = FVector::VectorPlaneProject(Velocity, Forward);
    FVector ForwardVelocity = FVector::DotProduct(Velocity, Forward) * Forward;

    FVector DriftForce = -LateralVelocity * (1.0f - DriftFactor) * 1000.0f;
    FVector RollingResistance = -ForwardVelocity * 0.05f;

    Chassis->AddForce(DriftForce + RollingResistance);
}

void AVehicleBase::LimitWheelRotationDirection()
{
    // Example for a wheel component named FrontLeftWheel
    if (!FL_Wheel) return;

    FVector AngularVelocity = FL_Wheel->GetPhysicsAngularVelocityInDegrees();

    // Let's assume we want to lock the wheel to rotate forward only on the Y-axis (pitch)
    if (AngularVelocity.Y < 0)
    {
        FVector ClampedAngularVelocity = AngularVelocity;
        ClampedAngularVelocity.Y = 0.f; // Prevent reverse rotation
        FL_Wheel->SetPhysicsAngularVelocityInDegrees(ClampedAngularVelocity);
    }
}
