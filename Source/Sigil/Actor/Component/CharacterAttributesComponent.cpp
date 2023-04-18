


#include "CharacterAttributesComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"

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

	OnHitPointsReachedZero.AddDynamic(this, &UCharacterAttributesComponent::OnDeath);
}


// Called every frame
void UCharacterAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//Regenerate HitPoints if allowed
	if (bCanRegenHitPoints)
	{
		RegenerateAttribute(HitPoints, MaximumHitPoints, HitPointRegenPercent);
	}

	//Regenerate MagicPoints if allowed
	if (bCanRegenMagicPoints)
	{
		RegenerateAttribute(MagicPoints, MaximumMagicPoints, MagicPointRegenPercent);
	}

	//Regenerate StaminaPoints if allowed
	if (bCanRegenStaminaPoints)
	{
		RegenerateAttribute(StaminaPoints, MaximumStaminaPoints, StaminaPointRegenPercent);
	}
}

void UCharacterAttributesComponent::RegenerateAttribute(float& CurrentAttribute, float& AttributeMaximum, float& AttributeRegenPercen)
{
	if (CurrentAttribute < AttributeMaximum)
	{
		/*	Goal: regenerate X attribute per second
			Where X is a percentage of AttributeMaximum determined by the value of AttributeRegenPercent

			5% of 100

			If DeltaTime is 1 second then regen 5
			If DeltaTime is 0.5 seconds then regen 2.5
		*/

		//Get the amount that will be regenerated
		float RegenAmount = AttributeMaximum * (AttributeRegenPercen / 100);

		//Multiply the amount by DeltaTime
		float RegenAmountDelta = RegenAmount * GetWorld()->GetDeltaSeconds();

		//Set CurrentAttribute to equal the new value
		CurrentAttribute = UKismetMathLibrary::FClamp((CurrentAttribute + RegenAmountDelta), 0.0f, AttributeMaximum);
	}
}

void UCharacterAttributesComponent::IncreaseAttribute(float& CurrentAttribute, float& AttributeMaximum, float Value)
{
	//Add Value to CurrentAttribute
	CurrentAttribute += Value;

	//Clamp the end result
	CurrentAttribute = UKismetMathLibrary::FClamp(CurrentAttribute, 0.0f, AttributeMaximum);
}

void UCharacterAttributesComponent::ReduceAttribute(float& CurrentAttribute, float& AttributeMaximum, float Value)
{
	//Subtract Value from CurrentAttribute
	CurrentAttribute -= Value;

	//Clamp the end result
	CurrentAttribute = UKismetMathLibrary::FClamp(CurrentAttribute, 0.0f, AttributeMaximum);
}

void UCharacterAttributesComponent::IncreaseHitPoints(float Value)
{
	IncreaseAttribute(HitPoints, MaximumHitPoints, Value);
}

void UCharacterAttributesComponent::IncreaseMagicPoints(float Value)
{
	IncreaseAttribute(MagicPoints, MaximumMagicPoints, Value);
}

void UCharacterAttributesComponent::IncreaseStaminaPoints(float Value)
{
	IncreaseAttribute(StaminaPoints, MaximumStaminaPoints, Value);
}

void UCharacterAttributesComponent::OnDeath()
{
	//Stop regenerating attributes
	SetCanRegenHitPoints(false);
	SetCanRegenMagicPoints(false);
	SetCanRegenStaminaPoints(false);
}

void UCharacterAttributesComponent::ReduceHitPoints(float Value)
{
	ReduceAttribute(HitPoints, MaximumHitPoints, Value);

	if (HitPoints <= 0)
	{
		OnHitPointsReachedZero.Broadcast();
	}
}

void UCharacterAttributesComponent::ReduceMagicPoints(float Value)
{
	ReduceAttribute(MagicPoints, MaximumMagicPoints, Value);

	if (MagicPoints <= 0)
	{
		OnMagicPointsReachedZero.Broadcast();
	}
}

void UCharacterAttributesComponent::ReduceStaminaPoints(float Value)
{ 
	ReduceAttribute(StaminaPoints, MaximumStaminaPoints, Value);

	if (StaminaPoints <= 0)
	{
		OnStaminaPointsReachedZero.Broadcast();
	}
}

void UCharacterAttributesComponent::SetCanRegenHitPoints(bool InBool)
{
	if (bCanRegenHitPoints != InBool)
	{
		bCanRegenHitPoints = InBool;
	}
}

void UCharacterAttributesComponent::SetCanRegenMagicPoints(bool InBool)
{
	if (bCanRegenMagicPoints != InBool)
	{
		bCanRegenMagicPoints = InBool;
	}
}

void UCharacterAttributesComponent::SetCanRegenStaminaPoints(bool InBool)
{
	if (bCanRegenStaminaPoints != InBool)
	{
		bCanRegenStaminaPoints = InBool;
	}
}

