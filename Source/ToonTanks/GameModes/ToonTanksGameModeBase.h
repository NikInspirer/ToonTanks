// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool IsPlayerWon);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 GameStartDelay = 3;
	
private:
	void HandleGameStart();
	void HandleGameOver(bool IsPlayerWon);
	FORCEINLINE int32 GetTargetTurretsCount() const;

	UPROPERTY()
	APawnTank* PlayerPawn;

	UPROPERTY()
	APlayerControllerBase* PlayerControllerRef;

	int32 TargetTurrets;
};
