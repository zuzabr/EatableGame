// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdibleGM.h"
#include "Core/EdibleHUD.h"
#include "Core/EdiblePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Core/EdibleGameInstance.h"

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

    if (!(GetWorldTimerManager().IsTimerActive(MatchProgressionTimerHandle)))
    {
        GetWorldTimerManager().SetTimer(MatchProgressionTimerHandle, this, &AEdibleGM::GameProgression, ExpCountRate, true);
    }
}

void AEdibleGM::GameLost()
{
    GetWorldTimerManager().ClearTimer(MatchProgressionTimerHandle);
    SetPause(GetWorld()->GetFirstPlayerController());
    SetMatchState(EMatchState::Lose);    
}

void AEdibleGM::GameProgression()
{
    ++Exp;
    TimeMultiplier += 10.f;

// ***********Lose Logic Uncomment, when the game will be ready*****************
    /*if ((WrongEatableItems + WrongNonEatableItems + MissedItems)>10)
    {
        if (GetWorld())
        {
            const auto GameInst = GetWorld()->GetGameInstance<UEdibleGameInstance>();
            if (GameInst)
            {
                GameInst->SetCoins(Coins);
                GameInst->SetExp(Exp);
            }
        }
        GameLost();
    }*/

    if (TimeMultiplier <= 1000.0f)
    {
        TRange<float> In (0.0f, 1000.0f);
        TRange<float> Out (1.2f, 4.0f);
        const auto Rate = FMath::GetMappedRangeValueClamped(In, Out, Exp);
        UGameplayStatics::SetGlobalTimeDilation(this, Rate);
        UE_LOG(LogTemp, Display, TEXT("Dilation : %f"), UGameplayStatics::GetGlobalTimeDilation(this));
        
    }
}


void AEdibleGM::SetMatchState(EMatchState State)
{
    if (MatchState == State) return;
    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
