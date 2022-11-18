

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttributesComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIGIL_API UCharacterAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterAttributesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void ReduceHitPoints(float Value) { HitPoints -= Value; }

	UFUNCTION(BlueprintCallable)
		void ReduceMagicPoints(float Value) { MagicPoints -= Value; }

	UFUNCTION(BlueprintCallable)
		void ReduceStaminaPoints(float Value) { StaminaPoints -= Value; }

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit Points")
		float HitPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hit Points")
		float MaximumHitPoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Points")
		float HitPointRegenPercent = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Points")
		bool bCanRegenHitPoints = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magic Points")
		float MagicPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magic Points")
		float MaximumMagicPoints = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic Points")
		bool bCanRegenMagicPoints = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic Points")
		float MagicPointRegenPercent = 0.05f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina Points")
		float StaminaPoints;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina Points")
		float MaximumStaminaPoints = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Points")
		bool bCanRegenStaminaPoints = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Points")
		float StaminaPointRegenPercent = 0.25f;
};
