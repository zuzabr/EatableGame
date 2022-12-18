// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "EdibleCoreTypes.h"
#include "EdibleSpriteActor.generated.h"

class UPaperSprite;
class UPhysicsHandleComponent;

UCLASS()
class EDIBLEGAME_API AEdibleSpriteActor : public APaperSpriteActor
{
    GENERATED_BODY()

public:
    AEdibleSpriteActor();

    bool GetIsEatable() const;
    void SetActorInfo(const FSpawnActorInfo* SpawnInfo) { SpawnActorInfo = SpawnInfo; }

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EdibleSpriteActor")
    UPaperSprite* GetEatableActorSprite() const;

    void StartToGrabActor(UPrimitiveComponent* Comp, FVector Location, ETouchIndex::Type FingerIndex, bool Grab = true);
    void StopGrabActor(bool Grab = false);
    void UpdateActorLocation();

protected:
    virtual void Tick(float DeltaTime) override;

    const FSpawnActorInfo* SpawnActorInfo = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UPhysicsHandleComponent* PhysicsHandle;

    UPROPERTY(EditDefaultsOnly, Category = "EdibleSpriteActor")
    UPaperSprite* ItemSptite;

private:
    FTimerHandle CarryTimerHandle;
    ETouchIndex::Type Finger;
    bool bCarried = false;
};
