// Zuzabr Games 2022 All Rights Reserved


#include "UI/SettingsWidget.h"
#include "Components/Button.h"
#include "Menu/MenuGameMode.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Core/EdibleGameInstance.h"

void USettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ReturnToMenuButton)
    {
        ReturnToMenuButton->OnClicked.AddDynamic(this, &USettingsWidget::ReturnToMenu);
    }

    if (NextButton)
    {
        NextButton->OnClicked.AddDynamic(this, &USettingsWidget::OnNextTheme);
    }

    if (PreviousButton)
    {
        PreviousButton->OnClicked.AddDynamic(this, &USettingsWidget::OnPreviousTheme);
    }

    if (LeftEatableCheckBox)
    {
        LeftEatableCheckBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::SetEatableOnLeftSetting);
    }

    const UEnum* ThemeEnum = StaticEnum<EGameTheme>();
    MaxIndex = (ThemeEnum->NumEnums() - 1);
    if (GetWorld())
    {
        const auto GameInst = GetWorld()->GetGameInstance<UEdibleGameInstance>();
        if (GameInst)
        {
            CurrentIndex = GameInst->GetThemeIndex();
            SetCurrentGameTheme();
            GameInst->GetEatableOnLeft() ? LeftEatableCheckBox->SetCheckedState(ECheckBoxState::Checked)
                                         : LeftEatableCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
        }
    }
    
}

void USettingsWidget::ReturnToMenu()
{
    ApplySettings();
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->OpenMainMenu();
    }
}

void USettingsWidget::SetEatableOnLeftSetting(bool OnLeft)
{
    EatableOnLeft = OnLeft ? true : false;
}

void USettingsWidget::OnNextTheme() 
{    
    CurrentIndex = CurrentIndex + 1 < MaxIndex ? CurrentIndex + 1 : 0;
    SetCurrentGameTheme();
}

void USettingsWidget::OnPreviousTheme()
{
    CurrentIndex = CurrentIndex - 1 >= 0 ? CurrentIndex - 1 : MaxIndex-1;
    SetCurrentGameTheme();
}

void USettingsWidget::ApplySettings()
{
    if (GetWorld())
    {
        const auto GameInst = GetWorld()->GetGameInstance<UEdibleGameInstance>();
        if (GameInst)
        {
            GameInst->SetGameTheme(static_cast<EGameTheme>(CurrentIndex));
            GameInst->SetThemeIndex(CurrentIndex);
            GameInst->SetEatableOnLeft(EatableOnLeft);
        }
    }
}

void USettingsWidget::SetCurrentGameTheme()
{
    CurrentTheme = static_cast<EGameTheme>(CurrentIndex);
    const auto CurrentThemeText = UEnum::GetDisplayValueAsText<EGameTheme>(CurrentTheme);
    ThemeText->SetText(CurrentThemeText);
}
