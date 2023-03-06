


#include "SpellcastingComponent.h"

// Sets default values for this component's properties
USpellcastingComponent::USpellcastingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpellbookComponent = CreateDefaultSubobject<USpellbookComponent>(TEXT("Spellbook Component"));

	// ...
}


// Called when the game starts
void USpellcastingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	EquipSelectedSpell();

}


// Called every frame
void USpellcastingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellcastingComponent::EquipSelectedSpell()
{
	if (!PreparedSpells.IsEmpty())
	{
		if (PreparedSpells[SelectedSpellIndex])
		{
			EquippedSpell = PreparedSpells[SelectedSpellIndex];
		}
	}
}

void USpellcastingComponent::SetSelectedSpellIndex(int NewIndex)
{
	if (NewIndex >= 0 && NewIndex < PreparedSpells.Num())
	{
		SelectedSpellIndex = NewIndex;

		EquipSelectedSpell();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("NewIndex must be between 0 and the Length of PreparedSpells-1"));
	}
}

void USpellcastingComponent::AddNewPreparedSpell(UDA_SpellInfo* NewSpell)
{
	if (NewSpell)
	{
		if (!PreparedSpells.Contains(NewSpell))
		{
			PreparedSpells.Add(NewSpell);
		}
	}
}

void USpellcastingComponent::RemovePreparedSpell(UDA_SpellInfo* InSpellInfo)
{
	if (InSpellInfo)
	{
		if (PreparedSpells.Contains(InSpellInfo))
		{
			PreparedSpells.Remove(InSpellInfo);
		}
	}
}

