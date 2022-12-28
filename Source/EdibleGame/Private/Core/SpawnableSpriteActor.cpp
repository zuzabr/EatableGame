// Zuzabr Games 2022 All Rights Reserved


#include "Core/SpawnableSpriteActor.h"

bool ASpawnableSpriteActor::GetIsEatable() const
{
    return SpawnActorInfo != nullptr ? SpawnActorInfo->bEatable : false;
}

UPaperSprite* ASpawnableSpriteActor::GetEatableActorSprite() const
{
    if (SpawnActorInfo != nullptr && SpawnActorInfo->ItemSptite != nullptr)
    {
        return SpawnActorInfo->ItemSptite;
    }
    else
    {
        return ItemSptite;
    }
}

void ASpawnableSpriteActor::IntendToDestroy()
{
    SetLifeSpan(0.1f);
}
