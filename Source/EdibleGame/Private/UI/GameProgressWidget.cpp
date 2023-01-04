// Zuzabr Games 2022 All Rights Reserved

#include "UI/GameProgressWidget.h"
#include "Components/Button.h"
#include "Core/EdibleGM.h"
#include "Core/EdibleGameInstance.h"

void UGameProgressWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (PauseButton)
    {
        PauseButton->OnPressed.AddDynamic(this, &UGameProgressWidget::OnPauseSet);
    }

    if (GetWorld())
    {
        GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
    }
}

bool UGameProgressWidget::GetEatableOnLeft() const
{
    if (!GetWorld()) return true;

    const auto GameInst = GetWorld()->GetGameInstance<UEdibleGameInstance>();
    if (!GameInst) return true;
    return GameInst->GetEatableOnLeft();
}

void UGameProgressWidget::OnPauseSet()
{

    if (GameMode && GetOwningPlayer())
    {
        GameMode->SetPause(GetOwningPlayer());
    }
}
