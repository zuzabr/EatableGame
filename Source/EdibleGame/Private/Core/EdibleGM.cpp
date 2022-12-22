// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdibleGM.h"
#include "Core/EdibleHUD.h"
#include "Core/EdiblePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/BorderActor.h"

AEdibleGM::AEdibleGM()
{
    HUDClass = AEdibleHUD::StaticClass();
    PlayerControllerClass = AEdiblePlayerController::StaticClass();
    
}

void AEdibleGM::StartPlay()
{
    Super::StartPlay();
    StartGame();
}

bool AEdibleGM::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchState(EMatchState::Pause);
    }
    return PauseSet;
}

bool AEdibleGM::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(EMatchState::InProgress);
    }

    return PauseCleared;
}

void AEdibleGM::StartGame()
{
    if (IsPaused())
    {
        ClearPause();
    }
    OnGameStarted.Broadcast();
    SetMatchState(EMatchState::InProgress);
}

void AEdibleGM::GameLost()
{
    SetMatchState(EMatchState::Lose);
}




void AEdibleGM::SetMatchState(EMatchState State)
{
    if (MatchState == State) return;
    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
