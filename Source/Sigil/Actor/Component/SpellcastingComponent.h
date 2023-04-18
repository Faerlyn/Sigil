

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellcastingComponent.generated.h"

class UDA_SpellInfo;
class USpellbookComponent;

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

	UPROPERTY(VisibleAnywhere)
		USpellbookComponent* SpellbookComponent;

	//Stores any spells prepared by the player (any spell added to the spell selection bar is 'prepared')
	UPROPERTY(VisibleAnywhere)
		TArray<UDA_SpellInfo*> PreparedSpells;

	//The currently equipped spell
	UPROPERTY(VisibleAnywhere)
		UDA_SpellInfo* EquippedSpell;

	//The index of the currently equipped spell
	UPROPERTY(VisibleAnywhere)
		int SelectedSpellIndex = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Getter for SpellbookComponent
	UFUNCTION(BlueprintCallable)
		USpellbookComponent* GetSpellbookComponent() { return SpellbookComponent; }

	//Getter for the PreparedSpells array
	UFUNCTION(BlueprintCallable)
		TArray<UDA_SpellInfo*> GetPreparedSpells() { return PreparedSpells; }

	//Setter for the PreparedSpells array
	UFUNCTION(BlueprintCallable)
		void SetPreparedSpells(TArray<UDA_SpellInfo*> NewPreparedSpells) { PreparedSpells = NewPreparedSpells; }

	//Getter for EquippedSpell
	UFUNCTION(BlueprintCallable)
		UDA_SpellInfo* GetEquippedSpell() { return EquippedSpell; }

	/// <summary>
	/// Equips the spell at SelectedSpellIndex of PreparedSpells (if valid).
	/// </summary>
	/// <returns>Returns true if the spell was equipped successfully. Returns false if the PreparedSpells array is empty or the element at SelectedSpellIndex is not valid.</returns>
	UFUNCTION(BlueprintCallable)
		bool EquipSelectedSpell();

	//Getter for SelectedSpellIndex
	UFUNCTION(BlueprintCallable)
		int GetSelectedSpellIndex() { return SelectedSpellIndex; }

	/// <summary>
	/// Setter for SelectedSpellIndex
	/// </summary>
	/// <param name="NewIndex">The integer value that SelectedSpellIndex will be set to. Must be a value between 0 and the length of PreparedSpells -1.</param>
	UFUNCTION(BlueprintCallable)
		void SetSelectedSpellIndex(int NewIndex);

	/// <summary>
	/// Adds the passed in spell to the PreparedSpells array (if valid and not pre-existing).
	/// </summary>
	/// <param name="NewSpell">The spell that will be added to PreparedSpells.</param>
	UFUNCTION(BlueprintCallable)
		void AddNewPreparedSpell(UDA_SpellInfo* NewSpell);

	/// <summary>
	/// Removes the passed in spell from the PreparedSpells array.
	/// </summary>
	/// <param name="InSpellInfo">The spell you want to remove from the PlayerSpells array</param>
	/// <returns>Returns true if the spell was removed successfully. Returns false if InSpellInfo is not valid or if it could not be found in the PreparedSpells array.</returns>
	UFUNCTION(BlueprintCallable)
		bool RemovePreparedSpell(UDA_SpellInfo* InSpellInfo);
};