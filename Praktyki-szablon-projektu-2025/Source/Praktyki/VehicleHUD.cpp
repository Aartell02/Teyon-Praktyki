// Copyright 2025 Teyon. All Rights Reserved.


#include "VehicleHUD.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Logging/LogMacros.h"

AVehicleHUD::AVehicleHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetFinder(TEXT("/Game/UI/WP_Race.WP_Race_C"));
    if (WidgetFinder.Succeeded())
    {
        WidgetClass = WidgetFinder.Class;
    }
}
void AVehicleHUD::BeginPlay()
{
    Super::BeginPlay();
    if (WidgetClass)
    {
        WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport();
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Widget is %s."), WidgetInstance ? TEXT("enabled") : TEXT("NOT enabled"));
}

