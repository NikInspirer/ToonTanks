// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "PawnBase.h"

#include "PawnTurret.generated.h"

class APawnTank;

/** */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
	explicit APawnTurret();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void HandleDestruction() override;

private:
	void CheckFireCondition();
	float ReturnDistanceToPlayer() const;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY()
	APawnTank* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange;
};
