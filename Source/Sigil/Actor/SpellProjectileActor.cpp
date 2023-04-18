


#include "SpellProjectileActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraComponent.h"

#include "../DataAsset/UDA_SpellInfo.h"

// Sets default values
ASpellProjectileActor::ASpellProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	NiagaraComponent_HitFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Hit FX"));
	NiagaraComponent_TrailFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail FX"));

	/*
		Attach the components to the actor
		- ProjectileMeshComponent
			- NiagaraComponent_TrailFX
			- NiagaraComponent_HitFX
	*/

	if (ProjectileMeshComponent)
	{
		SetRootComponent(ProjectileMeshComponent);

		if (NiagaraComponent_TrailFX)
		{
			NiagaraComponent_TrailFX->SetupAttachment(RootComponent);
		}

		if (NiagaraComponent_HitFX)
		{
			NiagaraComponent_HitFX->SetupAttachment(RootComponent);
		}
	}

	//Initialise the projectile properties
	SetMagicProperties();
}

// Called when the game starts or when spawned
void ASpellProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	//Initialise the projectile properties
	SetMagicProperties();

	//Bind delegates
	NiagaraComponent_HitFX->OnSystemFinished.AddDynamic(this, &ASpellProjectileActor::OnSystemFinished_HitFX);
	OnActorHit.AddDynamic(this, &ASpellProjectileActor::SpellProjectileHit);

	//Call PlayCastSFX
	PlayCastSFX();

	
}

// Called every frame
void ASpellProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add DeltaTime to ProjectileLifetime
	ProjectileLifetime += DeltaTime;

	//If ProjectileLifetime is greater than or equal to ProjectileTimeout
	if (ProjectileLifetime >= ProjectileTimeout)
	{
		//If the projectile has not been detonated yet
		if (!bDetonateDoOnce)
		{
			//Call DetonateProjectile
			DetonateProjectile();

			//Set bDetonateDoOnce to true
			bDetonateDoOnce = true;
		}
	}

}

void ASpellProjectileActor::SetInitialVariables(UDA_SpellInfo* InSpellInfo, UPrimitiveComponent* InTargetComponent)
{
	//Validate InSpellInfo
	if (InSpellInfo)
	{
		//Set ProjectileSpellInfo to InSpellInfo
		ProjectileSpellInfo = InSpellInfo;
	}

	//Validate InTargetComponent
	if (InTargetComponent)
	{
		//Set ProjectileTargetComponent to InTargetComponent
		ProjectileTargetComponent = InTargetComponent;
	}
}

void ASpellProjectileActor::SetMagicProperties()
{
	//Validate ProjectileSpellInfo
	if (ProjectileSpellInfo)
	{
		//Set the materials used by the projectile
		ApplySpellMaterials(ProjectileSpellInfo->MagicElementMaterials);

		//Set the meshes used by the projectile
		ApplyMeshes(ProjectileSpellInfo->Mesh);

		//Set the projectile's speeds
		SetProjectileSpeeds(ProjectileSpellInfo->Speed);

		//Configure homing for the projectile
		ConfigureProjectileHoming(ProjectileSpellInfo->bIsHoming);

		//If ProjectileSpellInfo's form is Flare
		if (ProjectileSpellInfo->Form == ESpellForm::Flare)
		{
			//Validate NiagaraComponent_TrailFX
			if (NiagaraComponent_TrailFX)
			{
				//Set auto activate to true
				NiagaraComponent_TrailFX->SetAutoActivate(true);

				//Active the component
				NiagaraComponent_TrailFX->Activate();

				//Validate ProjectileMeshComponent
				if (ProjectileMeshComponent)
				{
					//Hide the mesh
					ProjectileMeshComponent->SetHiddenInGame(true, false);
				}
			}
		}
		else
		{
			//Validate NiagaraComponent_TrailFX
			if (NiagaraComponent_TrailFX)
			{
				//Set auto activate to false
				NiagaraComponent_TrailFX->SetAutoActivate(false);

				//Validate ProjectileMeshComponent
				if (ProjectileMeshComponent)
				{
					//Do not hide the mesh
					ProjectileMeshComponent->SetHiddenInGame(false, false);
				}
			}
		}
	}
}

void ASpellProjectileActor::ApplySpellMaterials(FMagicElementMaterials InMagicElementMaterials)
{
	//Set the materials used by ProjectileMeshComponent
	ApplyMeshMaterials(InMagicElementMaterials);

	//Set the materials used by NiagaraComponent_HitFX
	ApplyFXMaterials_HitFX(InMagicElementMaterials);

	//Set the materials and colours used by NiagaraComponent_TrailFX
	ApplyFXMaterials_TrailFX(InMagicElementMaterials);
}

void ASpellProjectileActor::ApplyMeshMaterials(FMagicElementMaterials InMagicElementMaterials)
{
	//Validate ProjectileMeshComponent
	if (ProjectileMeshComponent)
	{
		//Set the mesh's material at index 0 to InMagicElementMaterials' MagicElementMaterial
		ProjectileMeshComponent->SetMaterial(0, InMagicElementMaterials.MagicElementMaterial);
	}
}

void ASpellProjectileActor::ApplyFXMaterials_HitFX(FMagicElementMaterials InMagicElementMaterials)
{
	//Validate NiagaraComponent_HitFX
	if (NiagaraComponent_HitFX)
	{
		//Set HitFX's BurstMaterial variable to InMagicElementMaterials's MagicElementMaterialEmissive
		NiagaraComponent_HitFX->SetVariableMaterial("BurstMaterial", InMagicElementMaterials.MagicElementMaterialEmissive);
	}
}

void ASpellProjectileActor::ApplyFXMaterials_TrailFX(FMagicElementMaterials InMagicElementMaterials)
{
	//Validate NiagaraComponent_TrailFX
	if (NiagaraComponent_TrailFX)
	{
		//Set TrailFX's UserRibbonPrimaryMaterial variable to InMagicElementMaterials's MagicElementMaterial
		NiagaraComponent_TrailFX->SetVariableMaterial("UserRibbonPrimaryMaterial", InMagicElementMaterials.MagicElementMaterial);

		//Set TrailFX's UserRibbonSecondaryMaterial variable to InMagicElementMaterials's MagicElementMaterialEmissive
		NiagaraComponent_TrailFX->SetVariableMaterial("UserRibbonSecondaryMaterial", InMagicElementMaterials.MagicElementMaterialEmissive);

		//Set TrailFX's UserRibbonPrimaryColour variable to InMagicElementMaterials's MagicPrimaryColour
		NiagaraComponent_TrailFX->SetVariableLinearColor("UserRibbonPrimaryColour", InMagicElementMaterials.MagicPrimaryColour);

		//Set TrailFX's UserRibbonSecondaryColour variable to InMagicElementMaterials's MagicSecondaryColour
		NiagaraComponent_TrailFX->SetVariableLinearColor("UserRibbonSecondaryColour", InMagicElementMaterials.MagicSecondaryColour);
	}
}

void ASpellProjectileActor::ApplyMeshes(UStaticMesh* InMesh)
{
	//Validate ProjectileMeshComponent and InMesh
	if (ProjectileMeshComponent && InMesh)
	{
		//Set ProjectileMeshComponent's static mesh to InMesh
		ProjectileMeshComponent->SetStaticMesh(InMesh);

		//Validate NiagaraComponent_HitFX
		if (NiagaraComponent_HitFX)
		{
			//Set HitFX's BurstStaticMesh variable to InMesh
			NiagaraComponent_HitFX->SetVariableStaticMesh("BurstStaticMesh", InMesh);
		}
	}
}

void ASpellProjectileActor::SetProjectileSpeeds(float InSpeed)
{
	//Validate ProjectileMovementComponent
	if (ProjectileMovementComponent)
	{
		//Set the projectile's maximum speed
		ProjectileMovementComponent->MaxSpeed = InSpeed;

		//Set the projectile's initial speed
		ProjectileMovementComponent->InitialSpeed = InSpeed;

		//Set the projectile's homing acceleration magnitude
		ProjectileMovementComponent->HomingAccelerationMagnitude = InSpeed * 6.0f;
	}
}

void ASpellProjectileActor::ConfigureProjectileHoming(bool IsAHomingProjectile)
{
	//Validate ProjectileMovementComponent
	if (ProjectileMovementComponent)
	{
		//Set bIsHomingProjectile to IsAHomingProjectile
		ProjectileMovementComponent->bIsHomingProjectile = IsAHomingProjectile;

		//Validate ProjectileTargetComponent
		if (ProjectileTargetComponent)
		{
			//Set HomingTargetComponent to ProjectileTargetComponent
			ProjectileMovementComponent->HomingTargetComponent = ProjectileTargetComponent;
		}
	}
}

void ASpellProjectileActor::PlayCastSFX()
{
	//Validate ProjectileSpellInfo
	if (ProjectileSpellInfo)
	{
		//Validate ProjectileAttenuationSettings
		if (ProjectileAttenuationSettings)
		{
			//Validate ProjectileSpellInfo's CastSFX
			if (ProjectileSpellInfo->CastSFX)
			{
				//Validate ProjectileMeshComponent
				if (ProjectileMeshComponent)
				{
					//Play CastFX where the projectile is
					UGameplayStatics::SpawnSoundAttached(ProjectileSpellInfo->CastSFX, ProjectileMeshComponent, NAME_None, FVector(0.0f, 0.0f, 0.0f), EAttachLocation::KeepRelativeOffset, true, 1.0f, 1.0f, 0.0f, ProjectileAttenuationSettings, nullptr, true);
				}
			}
		}
	}
}

void ASpellProjectileActor::PlayHitSFX()
{
	//Validate ProjectileSpellInfo
	if (ProjectileSpellInfo)
	{
		//Validate ProjectileAttenuationSettings
		if (ProjectileAttenuationSettings)
		{
			//Validate ProjectileSpellInfo's HitSFX
			if (ProjectileSpellInfo->HitSFX)
			{
				//Play HitFX where the projectile hit
				UGameplayStatics::SpawnSoundAtLocation(this, ProjectileSpellInfo->HitSFX, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 0.0f, ProjectileAttenuationSettings, nullptr, true);
			}
		}
	}
}

void ASpellProjectileActor::OnSystemFinished_HitFX(UNiagaraComponent* PSystem)
{
	//Destroy this actor
	Destroy();
}

void ASpellProjectileActor::DelayProjectileHoming()
{
	//Validate ProjectileSpellInfo
	if (ProjectileSpellInfo)
	{
		//If the spell has homing enabled
		if (ProjectileSpellInfo->bIsHoming)
		{
			//Valide ProjectileMovementComponent
			if (ProjectileMovementComponent)
			{
				//Set bIsHomingProjectile to false
				ProjectileMovementComponent->bIsHomingProjectile = false;

				//Start a timer using HomingDelay as the length, HomingTimerFinished will be called once the timer ends
				GetWorld()->GetTimerManager().SetTimer(HomingTimerHandle, this, &ASpellProjectileActor::HomingTimerFinished, HomingDelay, false);
			}
		}
	}
}

void ASpellProjectileActor::HomingTimerFinished()
{
	//Validate ProjectileMovementComponent
	if (ProjectileMovementComponent)
	{
		//Set bIsHomingProjectile to true
		ProjectileMovementComponent->bIsHomingProjectile = true;
	}
}

void ASpellProjectileActor::DetonateProjectile()
{
	//Deactivate NiagaraComponent_HitFX
	NiagaraComponent_HitFX->Activate(false);

	//Hide the projectile's mesh
	ProjectileMeshComponent->SetVisibility(false, false);

	//Disable the projectile's collisions
	ProjectileMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Play the HitSFX
	PlayHitSFX();

	//Deactivate NiagaraComponent_TrailFX
	NiagaraComponent_TrailFX->Deactivate();
}

void ASpellProjectileActor::SpellProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	//Validate ProjectileSpellInfo
	if (ProjectileSpellInfo)
	{
		//Iterate through ProjectileSpellInfo's SpellDamage array
		for (size_t i = 0; i < ProjectileSpellInfo->SpellDamage.Num(); i++)
		{
			//Get the current element's damage value
			float CurrentDamage = ProjectileSpellInfo->SpellDamage[i].DamageAmount;

			//Apply damage to the hit actor
			UGameplayStatics::ApplyDamage(OtherActor, CurrentDamage, GetInstigatorController(), GetInstigator(), ProjectileDamageType);
		}

		//Detonate the projectile
		DetonateProjectile();
	}
}
