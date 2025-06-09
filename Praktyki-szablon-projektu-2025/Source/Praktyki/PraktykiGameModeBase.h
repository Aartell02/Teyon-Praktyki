// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FPlayerRaceData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentLap = 1;

    UPROPERTY(BlueprintReadOnly)
    int32 NextCheckpoint = 0;

    UPROPERTY(BlueprintReadOnly)
    float CurrentLapTime = 0.0f;

    UPROPERTY(BlueprintReadOnly)
    float TotalRaceTime = 0.0f;

    UPROPERTY(BlueprintReadOnly)
    bool bStarted = false;

    UPROPERTY(BlueprintReadOnly)
    bool bFinished = false;
};

UCLASS()
class PRAKTYKI_API APraktykiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APraktykiGameModeBase();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    void OnPlayerHitCheckpoint(int32 CheckpointIndex);
    
    void StartRace();
    void FinishRace();
    void ResetRace();

    const FPlayerRaceData& GetRaceData() const;

    UPROPERTY(BlueprintReadOnly)
    int32 NumberOfLaps;

    UPROPERTY(BlueprintReadOnly)
    int32 TotalCheckpoints;

private:
    FPlayerRaceData PlayerRaceData;

};
