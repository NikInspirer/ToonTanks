// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerPawn)
	{
		PlayerPawn->PawnDestroy();
		HandleGameOver(false);

		if (PlayerControllerRef) { PlayerControllerRef->SetPlayerEnabled(false); }
	}
	else if (APawnTurret* DestroyedPawn = Cast<APawnTurret>(DeadActor))
	{
		DestroyedPawn->PawnDestroy();
		TargetTurrets--;
		if (TargetTurrets == 0) { HandleGameOver(true); }
	}
}

void AToonTanksGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretsCount();
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabled(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
		                                                                    &APlayerControllerBase::SetPlayerEnabled,
		                                                                    true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, GameStartDelay, false);
	}
}

void AToonTanksGameModeBase::HandleGameOver(bool IsPlayerWon)
{
	GameOver(IsPlayerWon);
}

int32 AToonTanksGameModeBase::GetTargetTurretsCount() const
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}
