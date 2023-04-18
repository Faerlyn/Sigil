

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SigilDamageHandlerComponent.generated.h"

class ASigilCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIGIL_API USigilDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USigilDamageHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ASigilCharacter* OwningCharacter;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the parent actor takes damage
	void TakeDamage(float BaseDamage, AController* EventInstigator, AActor* DamageCauser, const UDamageType* DamageTypeClass);
};
