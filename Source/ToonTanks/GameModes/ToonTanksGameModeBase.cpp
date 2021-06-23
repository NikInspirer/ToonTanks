// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TargetTurrets = GetTargetTurretsCount();
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	HandleGameStart();
}

void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerPawn)
	{
		PlayerPawn->PawnDestroy();
		HandleGameOver(false);
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
	UE_LOG(LogTemp, Log, TEXT("GameStarted"))
	GameStart();
}

void AToonTanksGameModeBase::HandleGameOver(bool IsPlayerWon)
{
	GameOver(IsPlayerWon);
	UE_LOG(LogTemp, Log, TEXT("GameOvered: %d"), IsPlayerWon)
}

int32 AToonTanksGameModeBase::GetTargetTurretsCount() const
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(this, APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}
