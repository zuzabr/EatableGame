// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EdibleCoreTypes.h"
#include "MenuGameMode.generated.h"

UCLASS()
class EDIBLEGAME_API AMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMenuGameMode();

    virtual void StartPlay() override;

    FOnMatchStateChangedSignature OnMatchStateChanged;
    void OpenSettingsMenu();
    void OpenMainMenu();

private:
    EMatchState MatchState = EMatchState::None;
    void SetMatchState(EMatchState State);
};
