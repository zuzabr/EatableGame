// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "EdibleCoreTypes.h"
#include "EdibleSpriteActor.generated.h"

class UPaperSprite;

UCLASS()
class EDIBLEGAME_API AEdibleSpriteActor : public APaperSpriteActor
{
    GENERATED_BODY()

public:
    AEdibleSpriteActor();

    bool GetIsEatable() const;
    void SetActorInfo(const FSpawnActorInfo* SpawnInfo) { SpawnActorInfo = SpawnInfo; }
    
    UFUNCTION()
    UPaperSprite* GetEatableActorSprite();

protected:
    virtual void BeginPlay() override;

    //UPROPERTY(BlueprintReadOnly, Category = "EdibleSpriteActor")
    const FSpawnActorInfo* SpawnActorInfo = nullptr;

private:
    
    bool Eatable = false;
};
