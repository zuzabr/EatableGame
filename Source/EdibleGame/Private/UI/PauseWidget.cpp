// Zuzabr Games 2022 All Rights Reserved


#include "UI/PauseWidget.h"
#include "Components/Button.h"
#include "Core/EdibleGM.h"

void UPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnPressed.AddDynamic(this, &UPauseWidget::OnClearPause);
    }
}

void UPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->ClearPause();
    }
}
