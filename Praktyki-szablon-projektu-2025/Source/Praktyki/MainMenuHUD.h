// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API AMainMenuHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    AMainMenuHUD();
    void ShowMainMenu();
    void ShowSettingsMenu();
    void SetFocus();

private:
    UPROPERTY()
    UUserWidget* CurrentWidget;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> SettingsWidgetClass;


};