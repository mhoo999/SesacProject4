
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildComponent_LDJ.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UBuildComponent_LDJ : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildComponent_LDJ();

protected:
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	// class PlayerBase_YMH* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class ASessac4ndProjectCharacter* Player;

	bool bIsBuildMode = false;
	bool bDoOnceMeshSet = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<UStaticMeshComponent> PreviewMeshFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UStaticMeshComponent* PreviewMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UStaticMesh* PreviewStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UMaterialInterface* ClockingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<class ASpikeTrap_LDJ> SpikeTrapFactory;

	FTransform BuildPreviewTransform;
public:	

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PreviewLoop();
	void ResetPreviewMesh();
	void PressBuildMode();
	void PressPlaceBuild();
};
