// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRaceFinished);

UCLASS()
class PRAKTYKI_API URaceWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual void NativeConstruct() override;

    int32 GetNumberOfLaps();
    int32 GetCurrentLap();


    UPROPERTY(BlueprintAssignable, Category = "Race")
    FOnRaceFinished OnRaceFinished;

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_Timer;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_LapCounter;

    UPROPERTY()
    bool bRaceFinishedBroadcasted = false;

};
