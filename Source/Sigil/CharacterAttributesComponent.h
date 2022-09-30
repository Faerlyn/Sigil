

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


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HitPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaxiumumHitPoints = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MagicPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaximumMagicPoints = 200;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float StaminaPoints;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaximumStaminaPoints = 50;
};
