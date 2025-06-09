// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SummaryWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;

UCLASS()
class PRAKTYKI_API USummaryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

protected:
    UFUNCTION()
    void OnExitButtonClicked();

    UFUNCTION()
    void OnRestartButtonClicked();

    void LoadSummaryData();

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock_FinalTime;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Exit;

    UPROPERTY(meta = (BindWidget))
    UButton* Button_Restart;
};