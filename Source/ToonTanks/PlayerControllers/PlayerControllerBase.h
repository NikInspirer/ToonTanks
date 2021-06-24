// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerBase.generated.h"

UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	void SetPlayerEnabled(bool bPlayerEnabled);
};
