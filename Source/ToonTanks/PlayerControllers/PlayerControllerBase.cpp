// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabled(bool bPlayerEnabled)
{
	if (bPlayerEnabled) { GetPawn()->EnableInput(this); }
	else { GetPawn()->DisableInput(this); }

	bShowMouseCursor = bPlayerEnabled;
}
