// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"


UCLASS()
class PRAKTYKI_API ACheckpointActor : public AActor
{
    GENERATED_BODY()

public:
    ACheckpointActor();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

public:
    UPROPERTY(EditAnywhere)
    int32 CheckpointIndex = 0;

private:
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* TriggerVolume;
};