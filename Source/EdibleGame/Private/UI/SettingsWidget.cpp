// Zuzabr Games 2022 All Rights Reserved


#include "UI/SettingsWidget.h"
#include "Components/Button.h"
#include "Menu/MenuGameMode.h"

void USettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ReturnToMenuButton)
    {
        ReturnToMenuButton->OnClicked.AddDynamic(this, &USettingsWidget::ReturnToMenu);
    }
}

void USettingsWidget::ReturnToMenu()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->OpenMainMenu();
    }
}
