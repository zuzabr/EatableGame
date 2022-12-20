// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "EdibleCoreTypes.h"
#include "EdibleSpriteActor.generated.h"

class UPaperSprite;
class UPhysicsHandleComponent;
class AEdiblePlayerController;

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

    void StartToGrabActor(UPrimitiveComponent* Comp, FVector Location, ETouchIndex::Type FingerIndex);
    void StopGrabActor();
    void UpdateActorLocation();

    void IntendToDestroy();

protected:
    virtual void BeginPlay() override;

    const FSpawnActorInfo* SpawnActorInfo = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    UPhysicsHandleComponent* PhysicsHandle;

    UPROPERTY(EditDefaultsOnly, Category = "EdibleSpriteActor")
    UPaperSprite* ItemSptite;

private:
    FTimerHandle CarryTimerHandle;
    ETouchIndex::Type Finger;
    AEdiblePlayerController* Controller;
    bool bCarried = false;
};
