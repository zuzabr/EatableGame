// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdibleHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "Core/EdibleGM.h"

void AEdibleHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), GameProgressWidgetClass));
    GameWidgets.Add(EMatchState::Lose, CreateWidget<UUserWidget>(GetWorld(), LoseWidgetClass));
    GameWidgets.Add(EMatchState::WaitingToStart, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
    GameWidgets.Add(EMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EMatchState::Settings, CreateWidget<UUserWidget>(GetWorld(), SettingsWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AEdibleHUD::OnMatchStateChanged);
        }
    }
}

void AEdibleHUD::OnMatchStateChanged(EMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}
