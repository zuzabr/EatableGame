// Zuzabr Games 2022 All Rights Reserved


#include "Core/EdibleGameInstance.h"

void UEdibleGameInstance::SetExp(int32 Exp)
{
    CurrentExp = Exp;
    FMath::Max(Exp, MaxExp);
}
