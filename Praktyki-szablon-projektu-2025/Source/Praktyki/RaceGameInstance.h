// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RaceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API URaceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
    float MaxGameTime = 300.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NumberOfLaps = 3;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString SelectedTrack;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NumberOfAI = 5;
    
};
