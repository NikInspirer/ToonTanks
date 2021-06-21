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

void APawnTurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APawnTurret::CheckFireCondition()
{
	if (PlayerPawn)
	{
		if (ReturnDistanceToPlayer() <= FireRange)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fire Success"))
		}
	}
}

float APawnTurret::ReturnDistanceToPlayer() const
{
	float Distance = 0.0f;
	if (PlayerPawn) { Distance = FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()); }
	return Distance;
}
