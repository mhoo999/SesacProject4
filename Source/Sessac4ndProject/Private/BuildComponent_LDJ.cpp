// zombie must die


#include "BuildComponent_LDJ.h"

#include "Sessac4ndProjectCharacter.h"
#include "SpikeTrap_LDJ.h"
#include "Camera/CameraComponent.h"

UBuildComponent_LDJ::UBuildComponent_LDJ()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBuildComponent_LDJ::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ASessac4ndProjectCharacter>(GetOwner());
}


void UBuildComponent_LDJ::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsBuildMode)
	{
		PreviewLoop();
	}
}

void UBuildComponent_LDJ::PreviewLoop()
{
	FVector StartPos = Player->GetFollowCamera()->GetComponentLocation();
	FVector EndPos = StartPos + Player->GetFollowCamera()->GetForwardVector() * 10000;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	FHitResult HitInfo;
	auto temp = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPos, EndPos, ECC_Visibility, Params);
	if (temp)
	{
		if (!bDoOnceMeshSet) this->ResetPreviewMesh();
	}

	BuildPreviewTransform.SetLocation(HitInfo.Location);
	BuildPreviewTransform.SetRotation(FQuat(0));
	BuildPreviewTransform.SetScale3D(FVector(1));

	PreviewMeshComp->SetWorldTransform(BuildPreviewTransform);
}

void UBuildComponent_LDJ::ResetPreviewMesh()
{
	auto temp = Player->AddComponentByClass(PreviewMeshFactory, false, BuildPreviewTransform, false);
	PreviewMeshComp = Cast<UStaticMeshComponent>(temp);
	if (temp && !bDoOnceMeshSet)
	{
		PreviewMeshComp->SetStaticMesh(PreviewStaticMesh);
		PreviewMeshComp->SetMaterial(0, ClockingMesh);
		PreviewMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bDoOnceMeshSet = true;
	}
}

void UBuildComponent_LDJ::PressBuildMode()
{
	if (!bIsBuildMode) bIsBuildMode = true;
	else
	{
		bIsBuildMode = false;
		if (PreviewMeshComp)
		{
			PreviewMeshComp->SetStaticMesh(nullptr);
			PreviewMeshComp = nullptr;
		}
	}
	bDoOnceMeshSet = false;
}

void UBuildComponent_LDJ::PressPlaceBuild()
{
	if (bIsBuildMode)
	{
		GetWorld()->SpawnActor<ASpikeTrap_LDJ>(SpikeTrapFactory, BuildPreviewTransform);
	}
}

