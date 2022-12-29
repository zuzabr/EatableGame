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
    ABomb();
    virtual void StartInteract() override;

protected:
    virtual void BeginPlay() override;
    UFUNCTION()
    void OnBombDestroyed(AActor* DestroyedActor);

private:
    bool bNeutralized = false;
};
