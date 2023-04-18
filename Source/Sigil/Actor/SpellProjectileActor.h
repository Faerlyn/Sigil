

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Library/Struct/SpellStructs.h"
#include "SpellProjectileActor.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;

class UDA_SpellInfo;

UCLASS()
class SIGIL_API ASpellProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The spell this projectile is representing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = true), Category = "Spell Projectile | Reference")
		UDA_SpellInfo* ProjectileSpellInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Projectile | Reference")
		TSubclassOf<UDamageType> ProjectileDamageType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = true), Category = "Spell Projectile | Reference")
		UPrimitiveComponent* ProjectileTargetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Components")
		UNiagaraComponent* NiagaraComponent_HitFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Components")
		UNiagaraComponent* NiagaraComponent_TrailFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Components")
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Components")
		UStaticMeshComponent* ProjectileMeshComponent;

	//Tracks how long the projectile has existed for
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Settings")
		float ProjectileLifetime = 0.0f;

	//The projectile will selfdestruct after being active for this amount of time (seconds).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Settings")
		float ProjectileTimeout = 10.0f;

	//The delay (in seconds) before the projectile will start homing in on its target.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spell Projectile | Settings")
		float HomingDelay = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Spell Projectile | Settings")
		USoundAttenuation* ProjectileAttenuationSettings;

	FTimerHandle HomingTimerHandle;
	
	bool bDetonateDoOnce = false;

	//Sets most of the projectile's properties using ProjectileSpellInfo.
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties")
		void SetMagicProperties();

	/// <summary>
	/// Sets the materials the projectile's components.
	/// </summary>
	/// <param name="InMagicElementMaterials">A struct from ProjectileSpellInfo that contains the materials that will be used.</param>
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Magic Element Materials ")
		void ApplySpellMaterials(FMagicElementMaterials InMagicElementMaterials);

	/// <summary>
	/// Sets the materials used by the projectile's mesh component(s).
	/// </summary>
	/// <param name="InMagicElementMaterials">A struct from ProjectileSpellInfo that contains the materials that will be used.</param>
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Magic Element Materials | Mesh")
		void ApplyMeshMaterials(FMagicElementMaterials InMagicElementMaterials);

	/// <summary>
	/// Sets the materials used by NiagaraComponent_HitFX.
	/// </summary>
	/// <param name="InMagicElementMaterials">A struct from ProjectileSpellInfo that contains the materials that will be used.</param>
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Magic Element Materials | FX")
		void ApplyFXMaterials_HitFX(FMagicElementMaterials InMagicElementMaterials);

	/// <summary>
	/// Sets the materials and colours used by NiagaraComponent_TrailFX.
	/// </summary>
	/// <param name="InMagicElementMaterials">A struct from ProjectileSpellInfo that contains the materials and colours that will be used.</param>
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Magic Element Materials | FX")
		void ApplyFXMaterials_TrailFX(FMagicElementMaterials InMagicElementMaterials);

	/// <summary>
	/// Sets the static meshes used by the projectile's components.
	/// </summary>
	/// <param name="InMesh">The static mesh that will be used.</param>
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Static Mesh")
		void ApplyMeshes(UStaticMesh* InMesh);

	/// <summary>
	/// Sets the speeds used by the projectile.
	/// </summary>
	/// <param name="InSpeed">The speed value that will be used.</param>
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Movement")
		void SetProjectileSpeeds(float InSpeed);

	//Configures the projectile's homing settings
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | Magic Properties | Movement")
		void ConfigureProjectileHoming(bool IsAHomingProjectile);

	//Plays the CastSFX sound
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | SFX")
		void PlayCastSFX();

	//Plays the HitSFX sound
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile | SFX")
		void PlayHitSFX();

	//Called when NiagaraComponent_HitFX effect has finished playing.
	UFUNCTION()
		void OnSystemFinished_HitFX(UNiagaraComponent* PSystem);

	//If the projectile is homing, turns off homing until the timer finishes.
	UFUNCTION()
		void DelayProjectileHoming();

	//Called when the HomingTimerHandle timer is finished.
	UFUNCTION()
		void HomingTimerFinished();

	//Call this function when the projectile hits something. Niagara FX are activated, meshes are hidden, and sound effects are played.
	UFUNCTION(BlueprintCallable, Category = "Spell Projectile")
		void DetonateProjectile();

	//Called when the projectile hits another actor.
	UFUNCTION()
		void SpellProjectileHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Used to initialise actor properties before spawning the actor.
	void SetInitialVariables(UDA_SpellInfo* SpellDataAsset, UPrimitiveComponent* SpellTargetComponent);

};
