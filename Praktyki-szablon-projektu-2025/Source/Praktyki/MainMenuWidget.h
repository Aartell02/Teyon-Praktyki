// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class AMainMenuHUD;

UCLASS()
class PRAKTYKI_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnStartGameClicked();

    UFUNCTION()
    void OnSettingsClicked();

    void SetMenuHUD(AMainMenuHUD* InHUD)
    {
        MenuHUD = InHUD;
    }

    UFUNCTION()
    void OnQuitClicked();

protected:

    UPROPERTY(meta = (BindWidget))
    class UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UPROPERTY()
    AMainMenuHUD* MenuHUD;
};

