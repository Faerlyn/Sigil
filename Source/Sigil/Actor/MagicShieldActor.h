

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicShieldActor.generated.h"

class UNiagaraComponent;

UCLASS()
class SIGIL_API AMagicShieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicShieldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the actor receives any damage
	UFUNCTION()
		void ShieldReceiveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere)
		UMeshComponent* ShieldMeshComponent;

	UPROPERTY(EditAnywhere)
		UNiagaraComponent* ShieldNiagaraComponent;

	UPROPERTY(EditAnywhere, Category = "Shield | SFX")
		USoundBase* ShieldBlockSFX;

	UPROPERTY(EditAnywhere, Category = "Shield | SFX")
		USoundAttenuation* ShieldAttenuationSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shield | Settings")
		bool bIsActive = true;
	
	//Damage taken by the shield is reduced by this percentage
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 100), Category = "Shield | Stats")
		uint8 DamageReductionPercent = 50;

	//Stamina loss incurred when blocking is reduced by this percentage
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 100), Category = "Shield | Stats")
		uint8 BlockEfficiencyPercent = 25;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Getter for bIsActive
	UFUNCTION()
		bool GetIsActive() { return bIsActive; }

	//Makes the actor visible and enables collisions
	UFUNCTION(BlueprintCallable)
		void ActivateShield();

	//Makes the actor invisible and disables collisions
	UFUNCTION(BlueprintCallable)
		void DeactivateShield();
};
