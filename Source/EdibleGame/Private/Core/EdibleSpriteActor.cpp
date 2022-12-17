// Zuzabr Games 2022 All Rights Reserved

#include "Core/EdibleSpriteActor.h"


AEdibleSpriteActor::AEdibleSpriteActor() {}

bool AEdibleSpriteActor::GetIsEatable() const
{    
    return SpawnActorInfo!=nullptr ? SpawnActorInfo->bEatable : false;
}

UPaperSprite* AEdibleSpriteActor::GetEatableActorSprite()
{
    return SpawnActorInfo != nullptr ? SpawnActorInfo->ItemSptite : nullptr;
}

void AEdibleSpriteActor::BeginPlay()
{
    Super::BeginPlay();
}
