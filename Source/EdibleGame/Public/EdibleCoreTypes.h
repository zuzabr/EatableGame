#pragma once

#include "Engine/DataTable.h"
#include "PaperSprite.h"
#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "EdibleCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
    None = 0,
    WaitingToStart,
    Lose,
    InProgress,
    Pause,
    Settings
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);

UENUM(BlueprintType)
enum class EGameTheme : uint8
{
    None = 0,
    Farm,
    Space,
    UnderWater,
    Town
};

UENUM(BlueprintType)
enum class ESpawnActorType : uint8
{
    FallingActors,
    Coin,
    Buff,
    Bomb
};

USTRUCT(BlueprintType)
struct FSpawnActorInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    FText ActorName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info" )
    ESpawnActorType SpawnActorType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", meta = (EditCondition = "SpawnActorType==SpawnActorType::FallingActors"))
    bool bEatable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    UPaperSprite* ItemSptite = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    EGameTheme GameTheme;
};

