// Copyright 2025 Teyon. All Rights Reserved.


#include "MainMenuWidget.h"
#include "MainMenuHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"



void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();                     

    if (PlayGameButton)
        PlayGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayGameClicked);

    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
}

void UMainMenuWidget::OnPlayGameClicked()
{
    if (!MenuHUD) return;
    RemoveFromParent();
    MenuHUD->ShowSettingsMenu();
}


void UMainMenuWidget::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
