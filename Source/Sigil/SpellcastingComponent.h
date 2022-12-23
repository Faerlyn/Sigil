

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellbookComponent.h"
#include "UDA_SpellInfo.h"
#include "SpellcastingComponent.generated.h"

USpellbookComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIGIL_API USpellcastingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellcastingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpellbookComponent* SpellbookComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	USpellbookComponent* GetSpellbookComponent() { return SpellbookComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UDA_SpellInfo*> PreparedSpells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDA_SpellInfo* EquippedSpell;

};
