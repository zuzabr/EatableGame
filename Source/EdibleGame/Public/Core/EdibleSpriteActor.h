// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Core/SpawnableSpriteActor.h"
#include "EdibleCoreTypes.h"
#include "EdibleSpriteActor.generated.h"

class UPaperSprite;
class UPhysicsHandleComponent;
class AEdiblePlayerController;

UCLASS()
class EDIBLEGAME_API AEdibleSpriteActor : public ASpawnableSpriteActor
{
    GENERATED_BODY()

public:
    AEdibleSpriteActor();

    void StartToGrabActor(UPrimitiveComponent* Comp, FVector Location, ETouchIndex::Type FingerIndex);
    void StopGrabActor();
    void UpdateActorLocation();
    
    virtual void IntendToDestroy() override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UPhysicsHandleComponent* PhysicsHandle;

private:
    FTimerHandle CarryTimerHandle;
    ETouchIndex::Type Finger;
    AEdiblePlayerController* Controller;
    bool bCarried = false;
};
