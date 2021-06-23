// Copyright © 2021 Nikita Kuznetsov. All Rights Reserved.

#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/GameModes/ToonTanksGameModeBase.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealth = 200.0f;
	Health = 0.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	GameModeRef = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigatedBy, AActor* DamageCauser)
{
	if (0 < Health)
	{
		Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

		if (Health <= 0)
		{
			if (GameModeRef) { GameModeRef->ActorDied(GetOwner()); }
			else { UE_LOG(LogTemp, Warning, TEXT("HealthComponent has no reference to GameMode")) }
		}
	}
}
