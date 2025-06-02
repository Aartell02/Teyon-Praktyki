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
    virtual void BeginPlay() override;

private:

protected:

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> WidgetClass;

    UPROPERTY()
    UUserWidget* WidgetInstance;
};
