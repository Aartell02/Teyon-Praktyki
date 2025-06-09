// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VehicleHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AVehicleHUD : public AHUD
{
	GENERATED_BODY()

public:
    AVehicleHUD();

    UFUNCTION()
    void ShowCountdownAndBlockInput();

    UFUNCTION()
    void ShowSummaryAndBlockInput();

    UFUNCTION()
    void UnblockInput();

    virtual void BeginPlay() override;

protected:
    UPROPERTY()
    APawn* OwningPawn;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> SummaryWidgetClass;

    UPROPERTY()
    UUserWidget* SummaryWidgetInstance;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> CountdownWidgetClass;

    UPROPERTY()
    UUserWidget* CountdownWidgetInstance;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> WidgetClass;

    UPROPERTY()
    UUserWidget* WidgetInstance;
};
