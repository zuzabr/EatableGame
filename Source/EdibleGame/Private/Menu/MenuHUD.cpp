// Zuzabr Games 2022 All Rights Reserved


#include "Menu/MenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Menu/MenuGameMode.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EMatchState::WaitingToStart, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
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
        const auto GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AMenuHUD::OnMatchStateChanged);
        }
    }
}

void AMenuHUD::OnMatchStateChanged(EMatchState State)
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
