


#include "CharacterAttributesComponent.h"

// Sets default values for this component's properties
UCharacterAttributesComponent::UCharacterAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	HitPoints = MaximumHitPoints;
	MagicPoints = MaximumMagicPoints;
	StaminaPoints = MaximumStaminaPoints;

}


// Called every frame
void UCharacterAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bCanRegenHitPoints)
	{
		if (HitPoints < MaximumHitPoints)
		{
			HitPoints += (MaximumHitPoints * (HitPointRegenPercent / 100));
		}
	}

	if (bCanRegenMagicPoints)
	{
		if (MagicPoints < MaximumMagicPoints)
		{
			MagicPoints += (MaximumMagicPoints * (MagicPointRegenPercent / 100));
		}
	}

	if (bCanRegenStaminaPoints)
	{
		if (StaminaPoints < MaximumStaminaPoints)
		{
			StaminaPoints += (MaximumStaminaPoints * (StaminaPointRegenPercent / 100));
		}
	}
}

void UCharacterAttributesComponent::ReduceHitPoints(float Value)
{
	HitPoints -= Value;

	HitPoints = UKismetMathLibrary::Clamp(HitPoints, 0.0f, MaximumHitPoints);
}

void UCharacterAttributesComponent::ReduceMagicPoints(float Value)
{
	MagicPoints -= Value;

	MagicPoints = UKismetMathLibrary::Clamp(MagicPoints, 0.0f, MaximumMagicPoints);
}

void UCharacterAttributesComponent::ReduceStaminaPoints(float Value)
{ 
	StaminaPoints -= Value;

	StaminaPoints = UKismetMathLibrary::Clamp(StaminaPoints, 0.0f, MaximumStaminaPoints);
}

