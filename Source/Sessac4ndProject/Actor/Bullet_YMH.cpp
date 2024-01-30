// zombie must die


#include "Actor/Bullet_YMH.h"

#include "EngineUtils.h"
#include "Character/Player/PlayerBase_YMH.h"
#include "Character/Player/PlayerFireComp_YMH.h"
#include "Components/BoxComponent.h"
#include "PlayerController/PlayerController_YMH.h"

ABullet_YMH::ABullet_YMH()
{
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule Component"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetRelativeScale3D(FVector(0.05f));
	capsuleComp->SetBoxExtent(FVector(10.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(0.05f, 0.01f, 0.01f));
}

void ABullet_YMH::BeginPlay()
{
	Super::BeginPlay();

	// auto owner = Cast<APlayerBase_YMH>();
	// auto player = Cast<APlayerBase_YMH>(newOwner);
	// FindOwner();

	// pc = Cast<APlayerController_YMH>(GetWorld()->GetFirstPlayerController());
	// auto player = Cast<APlayerBase_YMH>(pc->GetPawn());
	//
	// destination = player->FireComp->bulletDropPoint;
	// direction = destination - GetActorLocation();
	// direction.Normalize();
	
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
	// FVector v = direction * bulletSpeed;
	FVector v = GetActorForwardVector() * bulletSpeed;
	SetActorLocation(p0 + v * DeltaTime);
}

void ABullet_YMH::OnBoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto begin = Cast<AActor>(OtherActor);
	this->Destroy();
}

// void ABullet_YMH::FindOwner()
// {
// 	for (TActorIterator<APlayerBase_YMH> it(GetWorld()); it; ++it)
// 	{
// 		APlayerBase_YMH* otherActor = *it;
// 		Owner = otherActor;
// 	}
// }

