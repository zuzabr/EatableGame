// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EdibleCoreTypes.h"
#include "SettingsWidget.generated.h"

class UButton;
class UCheckBox;
class UTextBlock;

UCLASS()
class EDIBLEGAME_API USettingsWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UButton* ReturnToMenuButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PreviousButton;

    UPROPERTY(meta = (BindWidget))
    UButton* NextButton;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* LeftEatableCheckBox;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ThemeText;


private:
    UFUNCTION()
    void ReturnToMenu();

    UFUNCTION()
    void SetEatableOnLeftSetting(bool OnLeft);

    UFUNCTION()
    void OnNextTheme();

    UFUNCTION()
    void OnPreviousTheme();

    void ApplySettings();
    void SetCurrentGameTheme();
    
    bool EatableOnLeft = true;
    EGameTheme CurrentTheme;
    int32 CurrentIndex{0};
    int32 MaxIndex{0};
};
