


#include "SpellbookComponent.h"

#include "../../DataAsset/UDA_SpellInfo.h"

// Sets default values for this component's properties
USpellbookComponent::USpellbookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpellbookComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USpellbookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpellbookComponent::AddSpellToSpellbook(UDA_SpellInfo* InSpellInfo)
{
	//If InSpellInfo is valid
	if (InSpellInfo)
	{
		//Add it to the PlayerSpells array
		PlayerSpells.Add(InSpellInfo);
	}
}

bool USpellbookComponent::RemoveSpellFromSpellbook(UDA_SpellInfo* InSpellInfo)
{
	//If InSpellInfo is avlid
	if (InSpellInfo)
	{
		//If InSpellInfo can be found inside the PlayerSpells array
		if (PlayerSpells.IsValidIndex(PlayerSpells.Find(InSpellInfo)))
		{
			//Remove InSpellInfo from the PlayerSpells array
			PlayerSpells.Remove(InSpellInfo);

			//Return true to show that the operation was successful
			return true;
		}
	}

	//Return false to show that the operation was unsuccessful
	return false;
}

