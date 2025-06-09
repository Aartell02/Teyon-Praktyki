// Copyright 2025 Teyon. All Rights Reserved.


#include "CheckpointActor.h"
#include "PraktykiGameModeBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

ACheckpointActor::ACheckpointActor()
{
    PrimaryActorTick.bCanEverTick = false;
    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerVolume->SetGenerateOverlapEvents(true);
    RootComponent = TriggerVolume;
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);
    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);
    VisualMesh->SetVisibility(false); 
}

void ACheckpointActor::BeginPlay()
{
    Super::BeginPlay();

}

void ACheckpointActor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
    UPrimitiveComponent * OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult & SweepResult)
{
    if(APraktykiGameModeBase* GM = GetWorld()->GetAuthGameMode<APraktykiGameModeBase>())
    {
        GM->OnPlayerHitCheckpoint(CheckpointIndex);
    }
}

void ACheckpointActor::UpdateVisibility(bool bIsNext)
{
    if (bIsNext)
    {
        FVector BoxCenter = TriggerVolume->GetComponentLocation();
        FVector BoxExtent = TriggerVolume->GetScaledBoxExtent();
        FQuat BoxRotation = TriggerVolume->GetComponentQuat();
        DrawDebugBox(GetWorld(), BoxCenter, BoxExtent, BoxRotation, FColor::Red, true, -1, 0, 30.0f);
        VisualMesh->SetVisibility(true);
        UMaterialInterface* BaseMat = VisualMesh->GetMaterial(0);
        if (BaseMat)
        {
            UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMat, this);
            DynMat->SetScalarParameterValue(FName("Opacity"), 0.4f);
            VisualMesh->SetMaterial(0, DynMat);
        }
    }
    else
    {
        VisualMesh->SetVisibility(false);
    }
}