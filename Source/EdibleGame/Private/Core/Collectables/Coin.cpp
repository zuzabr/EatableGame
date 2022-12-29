// Zuzabr Games 2022 All Rights Reserved


#include "Core/Collectables/Coin.h"

void ACoin::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.0f);
}

void ACoin::StartInteract()
{
    IntendToDestroy();
}