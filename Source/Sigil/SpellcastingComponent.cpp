


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
	
}


// Called every frame
void USpellcastingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

