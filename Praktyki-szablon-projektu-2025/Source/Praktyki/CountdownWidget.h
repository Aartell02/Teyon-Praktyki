// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountdownWidget.generated.h"

class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownFinished);

UCLASS()
class PRAKTYKI_API UCountdownWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void StartCountdown();

    UFUNCTION()
    void UpdateCountdown();

    UPROPERTY(BlueprintAssignable, Category = "Countdown")
    FOnCountdownFinished OnCountdownFinished;

private:
    int32 CountdownValue = 3;
    FTimerHandle CountdownTimerHandle;

protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* CountdownText;

};