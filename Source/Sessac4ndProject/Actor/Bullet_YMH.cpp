// zombie must die


#include "Actor/Bullet_YMH.h"

#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerFireComp_YMH.h"
#include "PlayerController/PlayerController_YMH.h"

ABullet_YMH::ABullet_YMH()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABullet_YMH::BeginPlay()
{
	Super::BeginPlay();

	pc = Cast<APlayerController_YMH>(GetWorld()->GetFirstPlayerController());
	auto player = Cast<APlayerBase_YMH>(pc->GetPawn());
	destination = player->FireComp->bulletDropPoint;
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *destination.ToString());
	direction = destination - GetActorLocation();
	direction.Normalize();
	
	FTimerHandle deathTime;
	GetWorld()->GetTimerManager().SetTimer(deathTime, FTimerDelegate::CreateLambda([&]
	{
		this->Destroy();
	}), destroyTime, false);
}

void ABullet_YMH::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p0 = GetActorLocation();
	FVector v = direction * bulletSpeed;
	// FVector v = GetActorForwardVector() * bulletSpeed;
	SetActorLocation(p0 + v * DeltaTime);
}

