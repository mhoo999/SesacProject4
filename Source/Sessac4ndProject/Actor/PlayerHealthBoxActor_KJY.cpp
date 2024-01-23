// zombie must die


#include "Actor/PlayerHealthBoxActor_KJY.h"

#include "Character/Player/SMGPlayer_YMH.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerHealthBoxActor_KJY::APlayerHealthBoxActor_KJY()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));

}

// Called when the game starts or when spawned
void APlayerHealthBoxActor_KJY::BeginPlay()
{
	Super::BeginPlay();

	//collisionComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerHealthBoxActor_KJY::OnEnemyBeginOverlapped);
	
}

// Called every frame
void APlayerHealthBoxActor_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APlayerHealthBoxActor_KJY::OnEnemyBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어 체력 회복
	// 추후 모든 캐릭터 대상으로 변경
	//auto Playeractor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerBase_YMH::StaticClass());
	Player = Cast<APlayerBase_YMH>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	Player->currentHealth = Player->maxHelth;
	UE_LOG(LogTemp, Warning, TEXT("HP++"));
}

