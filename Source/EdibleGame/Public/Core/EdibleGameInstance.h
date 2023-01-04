// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EdibleCoreTypes.h"
#include "EdibleGameInstance.generated.h"

UCLASS()
class EDIBLEGAME_API UEdibleGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FName GetMenuLvlName() const { return MenuLvlName; }
    FName GetGameLvlName() const { return GameLvlName; }

    EGameTheme GetGameTheme() const { return GameTheme; }
    void SetGameTheme(EGameTheme Theme) { GameTheme = Theme; }
    bool GetEatableOnLeft() const { return bEatableOnLeft; }
    void SetEatableOnLeft(bool Left) { bEatableOnLeft = Left; }

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    int32 GetMaxExp() const { return MaxExp; }
    UFUNCTION(BlueprintCallable, Category = "Statistics")
    int32 GetCurrentExp() const { return CurrentExp; }
    UFUNCTION(BlueprintCallable, Category = "Statistics")
    int32 GetTotalCoins() const { return TotalCoins; }

    int32 GetThemeIndex() const { return ThemeIndex; }
    void SetThemeIndex(int32 Index) { ThemeIndex = Index; }

    void SetExp(int32 Exp);
    void SetCoins(int32 Coins) { TotalCoins += Coins; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Core Game Settings")
    FName MenuLvlName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Core Game Settings")
    FName GameLvlName = NAME_None;

private:
   
    int32 CurrentExp{0};
    int32 MaxExp{0};
    int32 TotalCoins{0};
    int32 ThemeIndex{0};

    bool bEatableOnLeft = true;
    EGameTheme GameTheme = EGameTheme::Fruits;

};
