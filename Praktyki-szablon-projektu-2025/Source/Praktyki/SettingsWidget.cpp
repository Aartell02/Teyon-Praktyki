// Copyright 2025 Teyon. All Rights Reserved.


#include "SettingsWidget.h"
#include "MainMenuHUD.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "RaceGameInstance.h"

void USettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();                 

    if (ApplyButton)
        ApplyButton->OnClicked.AddDynamic(this, &USettingsWidget::OnApplyClicked);

    if (BackButton)
        BackButton->OnClicked.AddDynamic(this, &USettingsWidget::OnBackClicked);

    LapsTextBox->SetText(FText::AsNumber(GetNumberOfLaps()));

}
void USettingsWidget::OnApplyClicked()
{
    const FString Text = LapsTextBox->GetText().ToString();
    const int32 LapsValue = FCString::Atoi(*Text);

    SetNumberOfLaps(LapsValue);

    OnBackClicked();
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
            MyGI->NumberOfLaps = Number;
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
            return MyGI->NumberOfLaps;
        }
    }
    return 0;
}