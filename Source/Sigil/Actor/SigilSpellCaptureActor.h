

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SigilSpellCaptureActor.generated.h"

class URotatingMovementComponent;
class USceneCaptureComponent2D;
class USceneComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class UTextureRenderTarget2D;

class UDA_SpellInfo;

UCLASS()
class SIGIL_API ASigilSpellCaptureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//ASigilSpellCaptureActor();
	ASigilSpellCaptureActor();

	void SetInitialVariables(UDA_SpellInfo* InSpellInfoRef, bool IsSpellbookRender);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SpellMeshComponent;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CaptureSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
		USceneCaptureComponent2D* SpellCaptureComponent;

	UPROPERTY(VisibleAnywhere)
		URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(EditAnywhere)
		UTextureRenderTarget2D* SpellTooltipRenderTarget;

	UPROPERTY(EditAnywhere)
		UTextureRenderTarget2D* SpellbookRenderTarget;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), VisibleAnywhere)
		UDA_SpellInfo* SpellInfoRef;

	UPROPERTY(EditAnywhere)
		TMap<ESpellForm, UStaticMesh*> MeshMap;

	UPROPERTY(EditAnywhere)
		TMap<EMagicElementType, UMaterialInterface*> MaterialMap;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), VisibleAnywhere)
		bool bIsSpellbookRender;

	UFUNCTION()
		void UpdateSpell();

	UFUNCTION()
		void UpdateSpellMesh(ESpellForm SpellForm);

	UFUNCTION()
		void UpdateSpellMaterial(FSpellElements SpellDamage);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
