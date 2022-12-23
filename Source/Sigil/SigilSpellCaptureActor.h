

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UDA_SpellInfo.h"
#include "SigilSpellCaptureActor.generated.h"

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
