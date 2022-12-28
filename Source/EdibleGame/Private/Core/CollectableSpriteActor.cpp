// Zuzabr Games 2022 All Rights Reserved


#include "Core/CollectableSpriteActor.h"



void ACollectableSpriteActor::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.0f);
}

void ACollectableSpriteActor::StartInteract()
{
    IntendToDestroy();
}