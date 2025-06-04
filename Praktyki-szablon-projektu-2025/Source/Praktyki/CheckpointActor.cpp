// Copyright 2025 Teyon. All Rights Reserved.


#include "CheckpointActor.h"
#include "PraktykiGameModeBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

ACheckpointActor::ACheckpointActor()
{
    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TriggerVolume->SetGenerateOverlapEvents(true);
    RootComponent = TriggerVolume;

    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnOverlapBegin);
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