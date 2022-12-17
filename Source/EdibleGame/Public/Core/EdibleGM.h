// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EdibleCoreTypes.h"
#include "EdibleGM.generated.h"

UCLASS()
class EDIBLEGAME_API AEdibleGM : public AGameModeBase
{
    GENERATED_BODY()

public:
    AEdibleGM();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    void OpenMainMenu();
    void OpenSettingsMenu();
    void StartGame();
    void GameLost();

private:
    EMatchState MatchState = EMatchState::None;
    void SetMatchState(EMatchState State);
};
