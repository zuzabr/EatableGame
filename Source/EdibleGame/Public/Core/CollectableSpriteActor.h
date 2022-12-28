// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Core/SpawnableSpriteActor.h"
#include "CollectableSpriteActor.generated.h"

UCLASS()
class EDIBLEGAME_API ACollectableSpriteActor : public ASpawnableSpriteActor
{
    GENERATED_BODY()

public:
    virtual void StartInteract() override;

protected:
    virtual void BeginPlay() override;
};
