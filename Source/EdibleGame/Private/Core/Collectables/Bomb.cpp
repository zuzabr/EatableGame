// Zuzabr Games 2022 All Rights Reserved


#include "Core/Collectables/Bomb.h"

void ABomb::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.0f);
}

void ABomb::StartInteract()
{
    IntendToDestroy();
}