// zombie must die


#include "Actor/ItemActor_KJY.h"

#include "Character/Player/PlayerBase_YMH.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AItemActor_KJY::AItemActor_KJY()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
}

// Called when the game starts or when spawned
void AItemActor_KJY::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActor_KJY::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor_KJY::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<APlayerBase_YMH>(GetWorld()->GetFirstPlayerController()->GetCharacter());

}

