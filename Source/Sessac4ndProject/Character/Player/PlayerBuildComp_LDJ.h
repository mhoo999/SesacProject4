// zombie must die

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "PlayerBaseComp_YMH.h"
#include "Character/CharacterBase_YMH.h"
#include "PlayerBuildComp_LDJ.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESSAC4NDPROJECT_API UPlayerBuildComp_LDJ : public UPlayerBaseComp_YMH
{
	GENERATED_BODY()
	
public:
	UPlayerBuildComp_LDJ();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	class UInputAction* IA_ChooseTrap1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_ChooseTrap2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_ChooseTrap3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_ChooseTrap4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_ChooseWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Inputs", meta = (AllowPrivateAccess))
	UInputAction* IA_PlaceTrap;
	
	bool bDoOnceMeshSet = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<UStaticMeshComponent> PreviewMeshFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UStaticMeshComponent* PreviewTrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UStaticMesh* PreviewTrapMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UMaterialInterface* EnableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class UMaterialInterface* DisableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<class ASpikeTrap_LDJ> SpikeTrapFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<class AFreezeTrap_LDJ> FreezeTrapFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<class APoisonTrap_LDJ> PoisonTrapFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	TSubclassOf<class AFlameThrowerTrap_LDJ> FlameTrapFactory;

	UPROPERTY()
	TSubclassOf<class ATrapBase> TrapFactory;
	
	FTransform BuildPreviewTransform;


public:
	void DoBuildSpikeTrap(const FInputActionValue& value);
	void DoBuildFreezeTrap(const FInputActionValue& value);
	void DoBuildPoisonTrap(const FInputActionValue& value);
	void DoBuildFlameTrap(const FInputActionValue& value);
	void DoEquipGun(const FInputActionValue& value);

	void PreviewLoop();
	void ResetPreviewMesh();
	void PressPlaceBuild();

	UFUNCTION()
	void OnTrapEndOverlapped(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnTrapBeginOverlapped(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	FTimerHandle Handle;

	int32 CollisionMeshCnt = 0;
	bool bBuildEnable = true;
};
