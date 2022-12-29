// Zuzabr Games 2022 All Rights Reserved


#include "Core/SpawnableSpriteActor.h"
#include "Engine/DataTable.h"


bool ASpawnableSpriteActor::GetIsEatable() const
{
    return SpawnActorInfo != nullptr ? SpawnActorInfo->bEatable : false;
}

UPaperSprite* ASpawnableSpriteActor::GetEatableActorSprite()
{
    if (SpawnActorInfo != nullptr && SpawnActorInfo->ItemSptite != nullptr)
    {
        return SpawnActorInfo->ItemSptite;
    }
    else if (SpawnActorInfo == nullptr)
    {
        static const FString DT_String = FString("DefaultItem");
        SpawnActorInfo = ItemInfo.DataTable->FindRow<FSpawnActorInfo>(ItemInfo.RowName, DT_String, true);
        return SpawnActorInfo != nullptr ? SpawnActorInfo->ItemSptite : nullptr;
    }
    return nullptr;
}

void ASpawnableSpriteActor::IntendToDestroy()
{
    SetLifeSpan(0.1f);
}
