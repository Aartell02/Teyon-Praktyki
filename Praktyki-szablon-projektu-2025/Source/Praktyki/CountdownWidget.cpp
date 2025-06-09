// Copyright 2025 Teyon. All Rights Reserved.


#include "CountdownWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"

void UCountdownWidget::NativeConstruct()
{
    Super::NativeConstruct();
    StartCountdown();
}

void UCountdownWidget::StartCountdown()
{
    CountdownValue = 3;
    UpdateCountdown();
    GetWorld()->GetTimerManager().SetTimer(
        CountdownTimerHandle, this, &UCountdownWidget::UpdateCountdown, 1.0f, true
    );
}

void UCountdownWidget::UpdateCountdown()
{
    if (CountdownValue > 0)
    {
        if (CountdownText)
        {
            CountdownText->SetText(FText::AsNumber(CountdownValue));
        }
        CountdownValue--;
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
        if (CountdownText)
        {
            CountdownText->SetText(FText::FromString(TEXT("START")));
        }

        OnCountdownFinished.Broadcast();
    }
}