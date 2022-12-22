// Zuzabr Games 2022 All Rights Reserved


#include "Menu/MenuGameMode.h"
#include "Menu/MenuHUD.h"
#include "Menu/MenuPlayerController.h"

AMenuGameMode::AMenuGameMode()
{
    HUDClass = AMenuHUD::StaticClass();
    PlayerControllerClass = AMenuPlayerController::StaticClass();
}

void AMenuGameMode::StartPlay()
{
    Super::StartPlay();
    OpenMainMenu();
}

void AMenuGameMode::OpenSettingsMenu()
{
    SetMatchState(EMatchState::Settings);
}

void AMenuGameMode::OpenMainMenu()
{
    SetMatchState(EMatchState::WaitingToStart);
}

void AMenuGameMode::SetMatchState(EMatchState State)
{
    if (MatchState == State) return;
    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
