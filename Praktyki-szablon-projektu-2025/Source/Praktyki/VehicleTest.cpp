// Copyright 2025 Teyon. All Rights Reserved.


#include "VehicleTest.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Logging/LogMacros.h"

// Sets default values
AVehicleTest::AVehicleTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
    Chassis->SetCenterOfMass(FVector(-25.f, 0.f, -10.f));
    Chassis->SetLinearDamping(0.2f);
    Chassis->SetAngularDamping(0.5f);

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
}

// Called when the game starts or when spawned
void AVehicleTest::BeginPlay()
{
    Super::BeginPlay();
    Chassis->SetSimulatePhysics(true);
    Chassis->WakeAllRigidBodies();
    SpringArm->SetWorldRotation(Chassis->GetComponentRotation());
    UE_LOG(LogTemp, Warning, TEXT("Chassis IsSimulatingPhysics: %s"), Chassis->IsSimulatingPhysics() ? TEXT("TRUE") : TEXT("FALSE"));
    UE_LOG(LogTemp, Warning, TEXT("Chassis Has Valid Physics Asset: %s"), Chassis->GetPhysicsAsset() ? TEXT("TRUE") : TEXT("FALSE"));
	
}
void AVehicleTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("Throttle", this, &AVehicleTest::Throttle);
    PlayerInputComponent->BindAxis("Steer", this, &AVehicleTest::Steer);

}
// Called every frame
void AVehicleTest::Tick(float DeltaTime)
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
            // Moment obrotowy wokó³ osi Z (pionowej)
            FVector Torque = FVector(0.f, 0.f, TurnInput * SteeringTorqueStrength);
            Chassis->AddTorqueInRadians(Torque);
        }
        ApplyFriction(DeltaTime);

    }
}


void AVehicleTest::ApplyFriction(float DeltaTime)
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

void AVehicleTest::Throttle(float Value)
{
    MovementInput.X = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AVehicleTest::Steer(float Value)
{
    TurnInput = FMath::Clamp(Value, -1.0f, 1.0f);
}