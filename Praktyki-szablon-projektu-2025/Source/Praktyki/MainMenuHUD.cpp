// Copyright 2025 Teyon. All Rights Reserved.


#include "MainMenuHUD.h"
#include "MainMenuWidget.h"
#include "SettingsWidget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Logging/LogMacros.h"


AMainMenuHUD::AMainMenuHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetBPClass(TEXT("/Game/UI/WP_MainMenu.WP_MainMenu_C"));
    if (WidgetBPClass.Succeeded())
    {
        MainMenuWidgetClass = WidgetBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetFinder(TEXT("/Game/UI/WP_SettingsMenu.WP_SettingsMenu_C"));
    if (WidgetFinder.Succeeded())
    {
        SettingsWidgetClass = WidgetFinder.Class;
    }

}
void AMainMenuHUD::BeginPlay() 
{
    ShowMainMenu();
}
void AMainMenuHUD::ShowMainMenu()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromParent();
        CurrentWidget = nullptr;
    }
    if (MainMenuWidgetClass)
    {
        UMainMenuWidget* MainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenu)
        {
            MainMenu->SetMenuHUD(this); 
            MainMenu->AddToViewport();
            CurrentWidget = MainMenu;

            SetFocus();
        }
    }
}

void AMainMenuHUD::ShowSettingsMenu()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromParent();
        CurrentWidget = nullptr;
    }

    if (SettingsWidgetClass)
    {
        USettingsWidget* Settings = CreateWidget<USettingsWidget>(GetWorld(), SettingsWidgetClass);
        if (Settings)
        {
            Settings->SetMenuHUD(this);
            Settings->AddToViewport();
            CurrentWidget = Settings;

            SetFocus();
        }
    }
}
void AMainMenuHUD::SetFocus() {
    APlayerController* PC = GetOwningPlayerController(); // or GetWorld()->GetFirstPlayerController()

    if (PC)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(CurrentWidget->TakeWidget()); 
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }
}