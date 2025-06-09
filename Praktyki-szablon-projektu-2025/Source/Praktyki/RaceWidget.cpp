// Copyright 2025 Teyon. All Rights Reserved.


#include "RaceWidget.h"
#include "Components/TextBlock.h"
#include "PraktykiGameModeBase.h"


void URaceWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void URaceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (APraktykiGameModeBase* GM = GetWorld()->GetAuthGameMode<APraktykiGameModeBase>())
    {
        FPlayerRaceData Data = GM->GetRaceData();
        if (Data.bFinished && !bRaceFinishedBroadcasted)
        {
            OnRaceFinished.Broadcast();
            bRaceFinishedBroadcasted = true;
            UE_LOG(LogTemp, Warning, TEXT("Race finished broadcast triggered."));
        }
        int32 TotalSeconds = FMath::FloorToInt(Data.TotalRaceTime);
        int32 Minutes = TotalSeconds / 60;
        int32 Seconds = TotalSeconds % 60;
        int32 Milliseconds = FMath::RoundToInt(FMath::Fmod(Data.TotalRaceTime, 1.0f) * 1000);

        FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, Milliseconds);
        if (TextBlock_Timer)
        {
            TextBlock_Timer->SetText(FText::FromString(TimeString));
        }
        FString LapsString = FString::Printf(TEXT("%d / %d"),GetCurrentLap(), GetNumberOfLaps());
        TextBlock_LapCounter->SetText(FText::FromString(LapsString));

    }
    
}

int32 URaceWidget::GetNumberOfLaps()
{
    if (APraktykiGameModeBase* GM = GetWorld()->GetAuthGameMode<APraktykiGameModeBase>())
    {
        return GM->NumberOfLaps;
    }
    return 0;
}

int32 URaceWidget::GetCurrentLap()
{

    if (APraktykiGameModeBase* GM = GetWorld()->GetAuthGameMode<APraktykiGameModeBase>())
    {
        FPlayerRaceData Data = GM->GetRaceData();
        return Data.CurrentLap;
    }
    return 0;
}