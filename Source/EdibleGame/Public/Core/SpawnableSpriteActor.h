// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "EdibleCoreTypes.h"
#include "SpawnableSpriteActor.generated.h"

class UPaperSprite;

UCLASS()
class EDIBLEGAME_API ASpawnableSpriteActor : public APaperSpriteActor
{
    GENERATED_BODY()

public:
    bool GetIsEatable() const;
    void SetActorInfo(const FSpawnActorInfo* SpawnInfo) { SpawnActorInfo = SpawnInfo; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EdibleSpriteActor")
    UPaperSprite* GetEatableActorSprite() const;

    virtual void IntendToDestroy();
    virtual void StartInteract(){};

protected:
    const FSpawnActorInfo* SpawnActorInfo = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "EdibleSpriteActor")
    UPaperSprite* ItemSptite;
};
