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

    int32 GetNumberOfLaps();
    void SetNumberOfLaps(int32 Number);

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 NumberOfLaps = 3;
};
