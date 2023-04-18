


#include "SigilSpellCaptureActor.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "../DataAsset/UDA_SpellInfo.h"

// Sets default values
ASigilSpellCaptureActor::ASigilSpellCaptureActor()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpellMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SpellMesh");
	CaptureSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("CaptureSpringArm");
	SpellCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SpellCapture2D");
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");

	RootComponent = SpellMeshComponent;

	CaptureSpringArmComponent->AttachToComponent(SpellMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpellCaptureComponent->AttachToComponent(CaptureSpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpellMeshComponent->SetRelativeRotation(FRotator(-20, -90, 0), false, nullptr, ETeleportType::None);
	SpellMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpellMeshComponent->bVisibleInSceneCaptureOnly = true;

	CaptureSpringArmComponent->TargetArmLength = 100;
	CaptureSpringArmComponent->bDoCollisionTest = false;
	CaptureSpringArmComponent->bInheritPitch = false;
	CaptureSpringArmComponent->bInheritYaw = false;
	CaptureSpringArmComponent->bInheritRoll = false;

	RotatingMovementComponent->RotationRate = FRotator(0, 90, 0);
	RotatingMovementComponent->bRotationInLocalSpace = false;

	SpellCaptureComponent->FOVAngle = 20.0f;

	SpellCaptureComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	
	//Add SpellMesh to SpellCapture's show only list
	SpellCaptureComponent->ShowOnlyComponent(SpellMeshComponent);

	
}

void ASigilSpellCaptureActor::SetInitialVariables(UDA_SpellInfo* InSpellInfoRef, bool IsSpellbookRender)
{
	SpellInfoRef = InSpellInfoRef;
	bIsSpellbookRender = IsSpellbookRender;
}

// Called when the game starts or when spawned
void ASigilSpellCaptureActor::BeginPlay()
{
	Super::BeginPlay();
	
	//If this render was not called by the spellbook, set the texture target to SpellTooltipRenderTarget. Otherwise, set it to SpellbookRenderTarget
	if (!bIsSpellbookRender)
	{
		SpellCaptureComponent->TextureTarget = SpellTooltipRenderTarget;
	}
	else
	{
		SpellCaptureComponent->TextureTarget = SpellbookRenderTarget;
	}

	//Update SpellMesh and its material
	UpdateSpell();
}

// Called every frame
void ASigilSpellCaptureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASigilSpellCaptureActor::UpdateSpell()
{
	//If SpellInfoRef is valid, update the mesh and material used in the capture
	if (SpellInfoRef)
	{
		UpdateSpellMesh(SpellInfoRef->Form);
		UpdateSpellMaterial(SpellInfoRef->SpellDamage[0]);
	}
}

void ASigilSpellCaptureActor::UpdateSpellMesh(ESpellForm SpellForm)
{
	//Get the spell form, find the corresponding mesh set it as the mesh
	if (UStaticMesh** value = MeshMap.Find(SpellForm))
	{
		SpellMeshComponent->SetStaticMesh(*value);	
	}
}

void ASigilSpellCaptureActor::UpdateSpellMaterial(FSpellElements SpellDamage)
{
	//Get the element type, find the corresponding material and set the mesh material
	if (UMaterialInterface** value = MaterialMap.Find(SpellDamage.ElementType))
	{
		SpellMeshComponent->SetMaterial(0, *value);
	}
}

