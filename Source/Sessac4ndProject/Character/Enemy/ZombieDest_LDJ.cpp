// zombie must die


#include "ZombieDest_LDJ.h"

#include "Game/ZMDGameStateBase_LDJ.h"
#include "Components/BoxComponent.h"

// Sets default values
AZombieDest_LDJ::AZombieDest_LDJ()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Component"));
	SetRootComponent(BodyComp);
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetBoxExtent(FVector(100));
}

// Called when the game starts or when spawned
void AZombieDest_LDJ::BeginPlay()
{
	Super::BeginPlay();

	GameState = Cast<AZMDGameStateBase_LDJ>(GetWorld()->GetGameState());
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AZombieDest_LDJ::OnZombieOverlap);
}

// Called every frame
void AZombieDest_LDJ::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieDest_LDJ::OnZombieOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TO DO : 좀비와 부딪히면 좀비가 사라지는 기능 만들기
	// auto temp = Cast<좀비베이스 들어갈 곳>(OtherActor);
	auto temp = Cast<AActor>(OtherActor);
	if (!temp) return;

	// GameState->Life--;
	temp->Destroy();
}

