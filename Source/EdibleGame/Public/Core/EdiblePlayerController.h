// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
#include "EdiblePlayerController.generated.h"

class AEdibleSpriteActor;

UCLASS()
class EDIBLEGAME_API AEdiblePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AEdiblePlayerController();

protected:
    virtual void SetupInputComponent() override;


    UFUNCTION()
    void StartCarry(ETouchIndex::Type FingerIndex, FVector Location);

    UFUNCTION()
    void StopCarry(ETouchIndex::Type FingerIndex, FVector Location);

private:
    TMap<ETouchIndex::Type, AEdibleSpriteActor*> GrabbedActors;
};
