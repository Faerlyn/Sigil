

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitPointsReachedZero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMagicPointsReachedZero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaPointsReachedZero);

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


protected:

	//The character's current Hit Points
	UPROPERTY(VisibleAnywhere, Category = "Character Attributes | Hit Points")
		float HitPoints;

	//The character's maximum Hit Points
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0), Category = "Character Attributes | Hit Points")
		float MaximumHitPoints = 400;

	//The percentage of the character's Hit Points that will be regenerated when bCanRegenHitPoints is true.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 100), Category = "Character Attributes | Hit Points")
		float HitPointRegenPercent = 0.1f;

	//Determines whether Hit Points can be regenerated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Attributes | Hit Points")
		bool bCanRegenHitPoints = true;

	//The character's current Magic Points
	UPROPERTY(VisibleAnywhere, Category = "Character Attributes | Magic Points")
		float MagicPoints;

	//The character's maximum Magic Points
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0), Category = "Character Attributes | Magic Points")
		float MaximumMagicPoints = 200;

	//The percentage of the character's Magic Points that will be regenerated when bCanRegenMagicPoints is true.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 100), Category = "Character Attributes | Magic Points")
		float MagicPointRegenPercent = 5.0f;

	//Determines whether Magic Points can be regenerated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Attributes | Magic Points")
		bool bCanRegenMagicPoints = true;

	//The character's current Stamina Points
	UPROPERTY(VisibleAnywhere, Category = "Character Attributes | Stamina Points")
		float StaminaPoints;

	//The character's maximum Stamina Points
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0), Category = "Character Attributes | Stamina Points")
		float MaximumStaminaPoints = 80;

	//The percentage of the character's Stamina Points that will be regenerated when bCanRegenStaminaPoints is true.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 100), Category = "Character Attributes | Stamina Points")
		float StaminaPointRegenPercent = 10.0f;

	//Determines whether Stamina Points can be regenerated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Attributes | Stamina Points")
		bool bCanRegenStaminaPoints = true;
	
	/// <summary>
	/// Regenerates X of the attribute per second. X is a percentage of the attribute's maximum value.
	/// </summary>
	/// <param name="CurrentAttribute">The attribute that you want to regenerate (HitPoints, MagicPoints, StaminaPoints etc.).</param>
	/// <param name="AttributeMaximum">The attribute's maximum value (MaximumHitPoints, MaximumMagicPoints, MaximumStaminaPoints etc.).</param>
	/// <param name="AttributeRegenPercent">The percentage of the attribute's maximum value that you want to regenerate (HitPointRegenPercent, MagicPointRegenPercent, StaminaPointRegenPercent etc.).</param>
	UFUNCTION()
		void RegenerateAttribute(float& CurrentAttribute, float& AttributeMaximum, float& AttributeRegenPercent);

	/// <summary>
	/// Increases the provided attribute by a specified amount
	/// </summary>
	/// <param name="CurrentAttribute">The attribute that you want to increase (HitPoints, MagicPoints, StaminaPoints etc.).</param>
	/// <param name="AttributeMaximum">The attribute's maximum value (MaximumHitPoints, MaximumMagicPoints, MaximumStaminaPoints etc.).</param>
	/// <param name="Value">The attribute will be increased by an amount equal to this variable</param>
	UFUNCTION()
		void IncreaseAttribute(float& CurrentAttribute, float& AttributeMaximum, float Value);

	/// <summary>
	/// Reduces the provided attribute by a specified amount
	/// </summary>
	/// <param name="CurrentAttribute">The attribute that you want to reduce (HitPoints, MagicPoints, StaminaPoints etc.).</param>
	/// <param name="AttributeMaximum">The attribute's maximum value (MaximumHitPoints, MaximumMagicPoints, MaximumStaminaPoints etc.).</param>
	/// <param name="Value">The attribute will be reduced by an amount equal to this variable</param>
	UFUNCTION()
		void ReduceAttribute(float& CurrentAttribute, float& AttributeMaximum, float Value);

public:

	//Called when HitPoints is less than or equal to 0.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHitPointsReachedZero OnHitPointsReachedZero;

	//Called when MagicPoints is less than or equal to 0.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMagicPointsReachedZero OnMagicPointsReachedZero;

	//Called when StaminaPoints is less than or equal to 0.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStaminaPointsReachedZero OnStaminaPointsReachedZero;

	//Getter for HitPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Hit Points")
		float GetCurrentHitPoints() { return HitPoints; }

	//Getter for MagicPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Magic Points")
		float GetCurrentMagicPoints() { return MagicPoints; }

	//Getter for StaminaPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina Points")
		float GetCurrentStaminaPoints() { return StaminaPoints; }

	//Getter for MaximumHitPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Hit Points")
		float GetMaximumHitPoints() { return MaximumHitPoints; }

	//Getter for MaximumMagicPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Magic Points")
		float GetMaximumMagicPoints() { return MaximumMagicPoints; }

	//Getter for MaximumStaminaPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina Points")
		float GetMaximumStaminaPoints() { return MaximumStaminaPoints; }

	//Increases HitPoints by the passed value.
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Hit Points")
		void IncreaseHitPoints(float Value);

	//Increases MagicPoints by the passed value.
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Magic Points")
		void IncreaseMagicPoints(float Value);

	//Increases StaminaPoints by the passed value.
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina Points")
		void IncreaseStaminaPoints(float Value);

	//Called when OnHitPointsReachedZero is broadcasted
	UFUNCTION()
		void OnDeath();

	//Reduces HitPoints by the passed value.
	//Broadcasts OnHitPointsReachedZero if HitPoints becomes less than or equal to 0.
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Hit Points")
		void ReduceHitPoints(float Value);

	//Reduces MagicPoints by the passed value.
	//Broadcasts OnMagicPointsReachedZero if MagicPoints becomes less than or equal to 0.
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Magic Points")
		void ReduceMagicPoints(float Value);

	//Reduces StaminaPoints by the passed value.
	//Broadcasts OnStaminaPointsReachedZero if StaminaPoints becomes less than or equal to 0.
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina Points")
		void ReduceStaminaPoints(float Value);

	//Sets the value of bCanRegenHitPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Hit Points")
	void SetCanRegenHitPoints(bool InBool);

	//Sets the value of bCanRegenMagicPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Magic Points")
	void SetCanRegenMagicPoints(bool InBool);

	//Sets the value of bCanRegenStaminaPoints
	UFUNCTION(BlueprintCallable, Category = "Character Attributes | Stamina Points")
	void SetCanRegenStaminaPoints(bool InBool);
};
