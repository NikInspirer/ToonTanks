// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#include "PawnTurret.h"

#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

APawnTurret::APawnTurret()
{
	FireRate = 2.0f;
	FireRange = 500.0f;
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void APawnTurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerPawn && (ReturnDistanceToPlayer() <= FireRange))
	{
		RotateTurret(PlayerPawn->GetActorLocation());
	}
}

void APawnTurret::CheckFireCondition()
{
	if (PlayerPawn && PlayerPawn->GeIsPlayerAlive())
	{
		if (ReturnDistanceToPlayer() <= FireRange)
		{
			Fire();
		}
	}
}

float APawnTurret::ReturnDistanceToPlayer() const
{
	float Distance = 0.0f;
	if (PlayerPawn) { Distance = FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()); }
	return Distance;
}
