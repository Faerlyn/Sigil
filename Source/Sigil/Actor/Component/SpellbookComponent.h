

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellbookComponent.generated.h"

class UDA_SpellInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIGIL_API USpellbookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellbookComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Stores any spells created by the player
	UPROPERTY(VisibleAnywhere)
		TArray<UDA_SpellInfo*> PlayerSpells;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Getter for the PlayerSpells array
	UFUNCTION(BlueprintCallable)
		TArray<UDA_SpellInfo*> GetPlayerSpells() { return PlayerSpells; }

	// Setter for the PlayerSpells array
	UFUNCTION(BlueprintCallable)
		void SetPlayerSpells(TArray<UDA_SpellInfo*> NewPlayerSpells) { PlayerSpells = NewPlayerSpells; }
	
	/// <summary>
	/// Adds the passed in spell to the PlayerSpells array.
	/// </summary>
	/// <param name="InSpellInfo">The spell that will be added to PlayerSpells.</param>
	UFUNCTION(BlueprintCallable)
		void AddSpellToSpellbook(UDA_SpellInfo* InSpellInfo);

	/// <summary>
	/// Removes the passed in spell from the PlayerSpells array.
	/// </summary>
	/// <param name="InSpellInfo">The spell you want to remove from the PlayerSpells array</param>
	/// <returns>Returns true if the spell was removed successfully. Returns false if InSpellInfo is not valid or if it could not be found in the PlayerSpells array.</returns>
	UFUNCTION(BlueprintCallable)
		bool RemoveSpellFromSpellbook(UDA_SpellInfo* InSpellInfo);
};