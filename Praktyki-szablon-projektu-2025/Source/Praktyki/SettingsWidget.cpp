// Copyright 2025 Teyon. All Rights Reserved.


#include "SettingsWidget.h"
#include "MainMenuHUD.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "RaceGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();                 

    if (StartButton)
        StartButton->OnClicked.AddDynamic(this, &USettingsWidget::OnStartClicked);

    if (BackButton)
        BackButton->OnClicked.AddDynamic(this, &USettingsWidget::OnBackClicked);

    LapsTextBox->SetText(FText::AsNumber(GetNumberOfLaps()));

}
void USettingsWidget::OnStartClicked()
{
    const FString Text = LapsTextBox->GetText().ToString();
    const int32 LapsValue = FCString::Atoi(*Text);

    SetNumberOfLaps(LapsValue);

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = false;
    }
    UGameplayStatics::OpenLevel(this, FName("TestMap"));
}
void USettingsWidget::OnBackClicked()
{
    if (!MenuHUD) return;

    RemoveFromParent();

    MenuHUD->ShowMainMenu(); 
}
void USettingsWidget::SetNumberOfLaps(int32 Number)
{
    if (UGameInstance* GI = GetWorld()->GetGameInstance())
    {
        if (URaceGameInstance* MyGI = Cast<URaceGameInstance>(GI))
        {
            MyGI->NumberOfLaps = Number < 1 ? 1: Number;
            UE_LOG(LogTemp, Warning, TEXT("Laps set to: %i"), Number);
        }
    }
}
int32 USettingsWidget::GetNumberOfLaps()
{
    if (UGameInstance* GI = GetWorld()->GetGameInstance())
    {
        if (URaceGameInstance* MyGI = Cast<URaceGameInstance>(GI))
        {
            return MyGI->GetNumberOfLaps();
        }
    }
    return 0;
}