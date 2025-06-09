// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
class AMainMenuHUD;

UCLASS()
class PRAKTYKI_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnBackClicked();

	void SetMenuHUD(AMainMenuHUD* InHUD)
	{
		MenuHUD = InHUD;
	}
	void SetNumberOfLaps(int32 Number);

	int32 GetNumberOfLaps();
protected:

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* LapsTextBox;

	UPROPERTY()
	AMainMenuHUD* MenuHUD;
};
