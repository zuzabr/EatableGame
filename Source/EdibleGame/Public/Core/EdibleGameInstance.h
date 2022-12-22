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

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Core Game Settings")
    FName MenuLvlName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Core Game Settings")
    FName GameLvlName = NAME_None;
};
