


#include "SigilDamageHandlerComponent.h"

#include "../Character/SigilCharacter.h"
#include "../Component/CharacterAttributesComponent.h"

// Sets default values for this component's properties
USigilDamageHandlerComponent::USigilDamageHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USigilDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	OwningCharacter = Cast<ASigilCharacter>(GetOwner());
	
}


// Called every frame
void USigilDamageHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USigilDamageHandlerComponent::TakeDamage(float BaseDamage, AController* EventInstigator, AActor* DamageCauser, const UDamageType* DamageTypeClass)
{
	if (OwningCharacter)
	{
		OwningCharacter->GetCharacterAttributesComponent()->ReduceHitPoints(BaseDamage);
	}
}

