// Zuzabr Games 2022 All Rights Reserved


#include "Core/Collectables/Coin.h"
#include "Core/EdibleGM.h"

void ACoin::BeginPlay()
{
    Super::BeginPlay();
    SetLifeSpan(2.0f);
}

void ACoin::StartInteract()
{
    if (GetWorld())
    {
        const auto GameMode = Cast<AEdibleGM>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->AddCoins(1);
        }
    }
    Destroy();
}