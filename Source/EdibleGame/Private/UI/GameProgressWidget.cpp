// Zuzabr Games 2022 All Rights Reserved


#include "UI/GameProgressWidget.h"
#include "Components/Button.h"
#include "Core/EdibleGM.h"

void UGameProgressWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (PauseButton)
    {
        PauseButton->OnPressed.AddDynamic(this, &UGameProgressWidget::OnPauseSet);
    }
}

void UGameProgressWidget::OnPauseSet()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
    if (GameMode && GetOwningPlayer())
    {
        GameMode->SetPause(GetOwningPlayer());
    }
}
