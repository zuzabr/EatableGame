// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Core/CollectableSpriteActor.h"
#include "Bomb.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class EDIBLEGAME_API ABomb : public ACollectableSpriteActor
{
    GENERATED_BODY()

public:
    virtual void StartInteract() override;

protected:
    virtual void BeginPlay() override;
};
