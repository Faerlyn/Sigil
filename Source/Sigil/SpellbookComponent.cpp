


#include "SpellbookComponent.h"

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
	if (InSpellInfo)
	{
		PlayerSpells.Add(InSpellInfo);
	}
}

bool USpellbookComponent::RemoveSpellFromSpellbook(UDA_SpellInfo* InSpellInfo)
{
	if (InSpellInfo)
	{
		if (PlayerSpells.IsValidIndex(PlayerSpells.Find(InSpellInfo)))
		{
			PlayerSpells.Remove(InSpellInfo);

			return true;
		}
	}

	return false;
}

