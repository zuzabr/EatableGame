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
    FOnGameStarted OnGameStarted;
    
    virtual void StartPlay() override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

    void StartGame();
    void GameLost();
    void GameProgression();

    void AddWrongEatableItems(int32 WrongEaten) { WrongEatableItems += WrongEaten; }
    void AddRightEatableItems(int32 RightEaten) { RightEatableItems += RightEaten; }
    void AddWrongNonEatableItems(int32 WrongNotEaten) { WrongNonEatableItems += WrongNotEaten; }
    void AddRightNonEatableItems(int32 RightNotEaten) { RightNonEatableItems += RightNotEaten; }
    void AddMissedItems(int32 Missed) { MissedItems += Missed; }
    void MultiplyExp(int32 ExpToAdd) { Exp += ExpToAdd; }
    void AddCoins(int32 CoinsNumber) { Coins += CoinsNumber; }

    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetWrongEatable() const { return WrongEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetRightEatable() const { return RightEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetWrongNotEatable() const { return WrongNonEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetRightNotEatable() const { return RightNonEatableItems; }
    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetMissedItems() const { return MissedItems; }
    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetExp() const { return Exp; }
    UFUNCTION(BlueprintCallable, Category = "Eatable GM")
    int32 GetCoins() const { return Coins; }
 
private:
    EMatchState MatchState = EMatchState::None;
    void SetMatchState(EMatchState State);

    FTimerHandle MatchProgressionTimerHandle;

    int32 WrongEatableItems{0};
    int32 RightEatableItems{0};

    int32 WrongNonEatableItems{0};
    int32 RightNonEatableItems{0};

    int32 MissedItems{0};

    float Exp{0};
    int32 Coins{0};

    float TimeMultiplier{0.0f};
    float ExpCountRate{1.f};
   

};
