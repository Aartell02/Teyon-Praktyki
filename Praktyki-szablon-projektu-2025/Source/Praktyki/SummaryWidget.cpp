// Copyright 2025 Teyon. All Rights Reserved.

#include "SummaryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PraktykiGameModeBase.h"
#include <Kismet/GameplayStatics.h>

void USummaryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (Button_Exit)
    {
        Button_Exit->OnClicked.AddDynamic(this, &USummaryWidget::OnExitButtonClicked);
    }
    if (Button_Restart)
    {
        Button_Restart->OnClicked.AddDynamic(this, &USummaryWidget::OnRestartButtonClicked);
    }

    LoadSummaryData();
}

void USummaryWidget::LoadSummaryData()
{
    if (APraktykiGameModeBase* GM = GetWorld()->GetAuthGameMode<APraktykiGameModeBase>())
    {
        FPlayerRaceData Data = GM->GetRaceData();
        int32 TotalSeconds = FMath::FloorToInt(Data.TotalRaceTime);
        int32 Minutes = TotalSeconds / 60;
        int32 Seconds = TotalSeconds % 60;
        int32 Milliseconds = FMath::RoundToInt(FMath::Fmod(Data.TotalRaceTime, 1.0f) * 1000);

        FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, Milliseconds);
        if (TextBlock_FinalTime)
        {
            TextBlock_FinalTime->SetText(FText::FromString(TimeString));
        }

    }
}

void USummaryWidget::OnExitButtonClicked()
{
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}
void USummaryWidget::OnRestartButtonClicked()
{
    
    if (APraktykiGameModeBase* GM = GetWorld()->GetAuthGameMode<APraktykiGameModeBase>())
    {
        GM->ResetRace();
    }
}
