


#include "SpellcastingComponent.h"

#include "../../DataAsset/UDA_SpellInfo.h"
#include "SpellbookComponent.h"

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
	
	//Call EquipSelectedSpell
	EquipSelectedSpell();

}


// Called every frame
void USpellcastingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USpellcastingComponent::EquipSelectedSpell()
{
	//If PreparedSpells is not empty
	if (!PreparedSpells.IsEmpty())
	{
		//Validate the element of PreparedSpells at SelectSpellIndex
		if (PreparedSpells[SelectedSpellIndex])
		{
			//Set EquippedSpell to this element
			EquippedSpell = PreparedSpells[SelectedSpellIndex];

			//Return true to show that the operation was successful
			return true;
		}
	}

	//Return false to show that the operation was unsuccessful
	return false;
}

void USpellcastingComponent::SetSelectedSpellIndex(int NewIndex)
{
	//If NewIndex is greater than or equal to 0 and less than the number of elements inside the PreparedSpells array
	if (NewIndex >= 0 && NewIndex < PreparedSpells.Num())
	{
		//Set SelectedSpellIndex to the value of NewIndex
		SelectedSpellIndex = NewIndex;

		//Equip the spell at SelectedSpellIndex
		EquipSelectedSpell();
	}
	else
	{
		//Print message to the log
		UE_LOG(LogTemp, Warning, TEXT("Information: USpellcastingComponent::SetSelectedSpellIndex NewIndex must be between 0 and the Length of PreparedSpells -1"));
	}
}

void USpellcastingComponent::AddNewPreparedSpell(UDA_SpellInfo* NewSpell)
{
	//Validate NewSpell
	if (NewSpell)
	{
		//If PreparedSpells does not contain NewSpell
		if (!PreparedSpells.Contains(NewSpell))
		{
			//Add NewSpell to the PreparedSpells array
			PreparedSpells.Add(NewSpell);
		}
	}
}

bool USpellcastingComponent::RemovePreparedSpell(UDA_SpellInfo* InSpellInfo)
{
	//Validate InSpellInfo
	if (InSpellInfo)
	{
		//If PreparedSpells contains InSpellInfo
		if (PreparedSpells.Contains(InSpellInfo))
		{
			//Remove InSpellInfo from the PreparedSpells array
			PreparedSpells.Remove(InSpellInfo);

			//Return true to show that the opertaion was successful
			return true;
		}
	}

	//Return false to show that the opertion was unsuccessful
	return false;
}

