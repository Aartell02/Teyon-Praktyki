// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiGameModeBase.h"
#include "CheckpointActor.h"
#include "VehicleHUD.h" 
#include "VehicleBase.h"
#include "VehiclePlayerController.h"
#include "RaceGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"
#include "EngineUtils.h"

APraktykiGameModeBase::APraktykiGameModeBase()
{
	HUDClass = AVehicleHUD::StaticClass();
	DefaultPawnClass = AVehicleBase::StaticClass();
	PlayerControllerClass = AVehiclePlayerController::StaticClass();
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    PrimaryActorTick.bCanEverTick = true;
}
void APraktykiGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    const URaceGameInstance* GI = GetGameInstance<URaceGameInstance>();

    NumberOfLaps = GI ? GI->NumberOfLaps : 3;
    TotalCheckpoints = 6;

    for (TActorIterator<ACheckpointActor> It(GetWorld()); It; ++It)
    {
        ACheckpointActor* CP = *It;
        if (CP)
        {
            CP->UpdateVisibility(CP->CheckpointIndex == PlayerRaceData.NextCheckpoint);
        }
    }
}
void APraktykiGameModeBase::Tick(float DeltaTime)
{
    if (!PlayerRaceData.bFinished)
    {
        PlayerRaceData.CurrentLapTime += DeltaTime;
        PlayerRaceData.TotalRaceTime += DeltaTime;
    }
    
}
void APraktykiGameModeBase::OnPlayerHitCheckpoint(int32 CheckpointIndex)
{
    if (PlayerRaceData.bFinished) return;
    if (!PlayerRaceData.bStarted) return;

    if (CheckpointIndex == PlayerRaceData.NextCheckpoint)
    {
        UE_LOG(LogTemp, Warning, TEXT("You hit checkpoint: %d"), PlayerRaceData.NextCheckpoint);
        PlayerRaceData.NextCheckpoint++;

        for (TActorIterator<ACheckpointActor> It(GetWorld()); It; ++It)
        {
            ACheckpointActor* CP = *It;
            if (CP)
            {
                CP->UpdateVisibility(CP->CheckpointIndex == PlayerRaceData.NextCheckpoint);
            }
        }
        if (PlayerRaceData.NextCheckpoint >= TotalCheckpoints)
        {
            PlayerRaceData.NextCheckpoint = 0;
            if(PlayerRaceData.CurrentLap < NumberOfLaps)PlayerRaceData.CurrentLap++;
            else 
            {
                PlayerRaceData.bFinished = true;
                UE_LOG(LogTemp, Warning, TEXT("Race finished! Total time: %.2f seconds"), PlayerRaceData.TotalRaceTime);
            }
            PlayerRaceData.CurrentLapTime = 0.f;
        }
    }
}


const FPlayerRaceData& APraktykiGameModeBase::GetRaceData() const
{
    return PlayerRaceData;
}

void APraktykiGameModeBase::StartRace()
{
    PlayerRaceData.bStarted = true;
    PlayerRaceData.TotalRaceTime = 0.f;
}
void APraktykiGameModeBase::FinishRace() 
{

}
void APraktykiGameModeBase::ResetRace() 
{
    UGameplayStatics::OpenLevel(this, TEXT("TestMap"));

}
