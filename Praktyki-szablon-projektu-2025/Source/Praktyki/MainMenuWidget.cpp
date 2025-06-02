// Copyright 2025 Teyon. All Rights Reserved.


#include "MainMenuWidget.h"
#include "MainMenuHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"



void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();                     

    if (StartGameButton)
        StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGameClicked);

    if (SettingsButton)
        SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);

    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
}

void UMainMenuWidget::OnStartGameClicked()
{

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = false;
    }
    UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void UMainMenuWidget::OnSettingsClicked()
{
    if (!MenuHUD) return;

    RemoveFromParent();

    MenuHUD->ShowSettingsMenu();
}

void UMainMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
