// Copyright 2025 Teyon. All Rights Reserved.


#include "VehicleHUD.h"
#include "VehicleBase.h"
#include "TimerManager.h"
#include "CountdownWidget.h"
#include "RaceWidget.h"
#include "PraktykiGamemodeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/LogMacros.h"

AVehicleHUD::AVehicleHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetFinder(TEXT("/Game/UI/WP_Race.WP_Race_C"));
    if (WidgetFinder.Succeeded())
    {
        WidgetClass = WidgetFinder.Class;
    }
    
    static ConstructorHelpers::FClassFinder<UUserWidget> CountdownWidgetFinder(TEXT("/Game/UI/WP_Countdown.WP_Countdown_C"));
    if (CountdownWidgetFinder.Succeeded())
    {
        CountdownWidgetClass = CountdownWidgetFinder.Class;
    }
    static ConstructorHelpers::FClassFinder<UUserWidget> SummaryWidgetFinder(TEXT("/Game/UI/WP_Summary.WP_Summary_C"));
    if (SummaryWidgetFinder.Succeeded())
    {
        SummaryWidgetClass = SummaryWidgetFinder.Class;
    }

}
void AVehicleHUD::BeginPlay()
{
    Super::BeginPlay();
    ShowCountdownAndBlockInput(); 
}

void AVehicleHUD::ShowCountdownAndBlockInput()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AVehicleBase* Vehicle = Cast<AVehicleBase>(PC->GetPawn()))
        {
            Vehicle->bInputBlocked = true;
            UE_LOG(LogTemp, Warning, TEXT("Input blocked on vehicle: %s"), *Vehicle->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Current Pawn is not a VehicleBase."));
        }
    }


    if (CountdownWidgetClass)
    {
        CountdownWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CountdownWidgetClass);
        if (CountdownWidgetInstance)
        {

            if (UCountdownWidget* TypedCountdown = Cast<UCountdownWidget>(CountdownWidgetInstance))
            {
                TypedCountdown->OnCountdownFinished.AddDynamic(this, &AVehicleHUD::UnblockInput);
            }

            CountdownWidgetInstance->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Countdown widget added to viewport"));

        }
    }

}

void AVehicleHUD::UnblockInput()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AVehicleBase* Vehicle = Cast<AVehicleBase>(PC->GetPawn()))
        {
            Vehicle->bInputBlocked = false;
            UE_LOG(LogTemp, Warning, TEXT("Input unblocked on vehicle: %s"), *Vehicle->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("UnblockInput: Current Pawn is not a VehicleBase."));
        }
        if (PC->GetPawn() != nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("PlayerController still possesses: %s"), *PC->GetPawn()->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("PlayerController does not possess any pawn!"));
        }
    }
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = false;
        UE_LOG(LogTemp, Warning, TEXT("InputMode set to GameOnly and mouse hidden after restart"));
    }

    if (CountdownWidgetInstance)
    {
        CountdownWidgetInstance->RemoveFromParent();
        CountdownWidgetInstance = nullptr;
    }

    if (WidgetClass)
    {
        URaceWidget* TypedRaceWidget = CreateWidget<URaceWidget>(GetWorld(), WidgetClass);
        if (TypedRaceWidget)
        {
            WidgetInstance = TypedRaceWidget;
            TypedRaceWidget->AddToViewport();
            TypedRaceWidget->OnRaceFinished.AddDynamic(this, &AVehicleHUD::ShowSummaryAndBlockInput);
            UE_LOG(LogTemp, Warning, TEXT("Successfully created and bound RaceWidget"));
        }
    }

    if (AGameModeBase* GM = GetWorld()->GetAuthGameMode())
    {
        if (APraktykiGameModeBase* MyGM = Cast<APraktykiGameModeBase>(GM))
        {
            MyGM->StartRace();
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Input unblocked after countdown."));
}


void AVehicleHUD::ShowSummaryAndBlockInput()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AVehicleBase* Vehicle = Cast<AVehicleBase>(PC->GetPawn()))
        {
            Vehicle->bInputBlocked = true;
            UE_LOG(LogTemp, Warning, TEXT("ShowSummary: bInputBlocked set to TRUE on vehicle: %s"), *Vehicle->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ShowSummary: Current Pawn is not AVehicleBase."));
        }
    }

    if (SummaryWidgetClass)
    {
        SummaryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), SummaryWidgetClass);
        if (SummaryWidgetInstance)
        {
            APlayerController* PC = GetOwningPlayerController();
            SummaryWidgetInstance->AddToViewport();
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(SummaryWidgetInstance->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;
            }

            UE_LOG(LogTemp, Warning, TEXT("Summary widget added to viewport"));

        }
    }
}