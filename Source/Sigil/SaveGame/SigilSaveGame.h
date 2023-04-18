

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Library/Struct/SpellStructs.h"
#include "SigilSaveGame.generated.h"

class UDA_SpellInfo;
class UDA_SpellMap;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:


protected:

	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Spells | Player Spells")
		TArray<FSpellProperties> PlayerSpells;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Spells | Player Spells")
		TArray<UDA_SpellInfo*> OutPlayerSpells;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Spells | Prepared Spells")
		TArray<FSpellProperties> PreparedSpells;

	UPROPERTY(EditAnywhere, Category = "Sigil Save Game | Spells ")
		UDA_SpellMap* SpellMap;

	//Used to store DataAsset spells, the integer stores the slot it was saved in.
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Spells | Prepared Spells")
		TMap<int, UDA_SpellInfo*> PreparedCoreSpells;

	//The first integer stores which prepared slot the spell was saved in, the second stores the index of PlayerSpells where the spell can be found.
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Spells | Prepared Spells")
		TMap<int, int> PreparedPlayerSpells;

	//Stores the length of the PreparedSpells array when saving the game.
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Spells | Prepared Spells")
		int PreparedSpellsLength;

	//Stores the player's name
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Player Info")
		FName PlayerName;

	//Stores the player's character transform
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Player Info")
		FTransform PlayerCharacterTransform;

	//Stores the player's controller rotation
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | Player Info")
		FRotator PlayerControllerRotation;

	//Stores the save slot's name
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | ")
		FString SaveSlotName;

	//Stores the player's user index
	UPROPERTY(VisibleAnywhere, Category = "Sigil Save Game | ")
		int UserIndex;

	/// <summary>
	/// Saves the player's created spells to the PlayerSpells array.
	/// </summary>
	/// <param name="InPlayerSpells">An array of the player's created spells.</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Save | Spells | Player Spells")
		void SavePlayerSpells(TArray<UDA_SpellInfo*> InPlayerSpells);

	/// <summary>
	/// Saves the player's prepared spells to the PreparedCoreSpells and PreparedPlayerSpells arrays.
	/// </summary>
	/// <param name="InPlayerSpells">An array of the player's created spells.</param>
	/// <param name="InPreparedSpells">An array of the player's prepared spells.</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Save | Spells | Prepared Spells")
		void SavePreparedSpells(TArray<UDA_SpellInfo*> InPlayerSpells, TArray<UDA_SpellInfo*> InPreparedSpells);

	/// <summary>
	/// Gets the player's created spells from the last time they saved.
	/// </summary>
	/// <returns>An array of the player's created spells.</returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Load Save | Spells | Player Spells")
		TArray<UDA_SpellInfo*> LoadPlayerSpells();

	/// <summary>
	/// Gets the player's prepared spells from the last time they saved.
	/// </summary>
	/// <returns>An array of the player's prepared spells.</returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Load Save | Spells | Prepared Spells")
		TArray<UDA_SpellInfo*> LoadPreparedSpells();

	/// <summary>
	/// Get an element from PreparedCoreSpells at the provided index and add it to the provided array.
	/// </summary>
	/// <param name="InArrayIndex">The index of the element we want to add to InSpellArray</param>
	/// <param name="InSpellArray">The array we want to add the prepared spell to</param>
	/// <returns>Returns true if the operation was successful</returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Load Save | Spells | Prepared Spells")
		bool TryLoadPreparedCoreSpells(int InArrayIndex, TArray<UDA_SpellInfo*>& InSpellArray);

	/// <summary>
	/// Get an element from PreparedPlayerSpells at the provided index and add it to the provided array.
	/// </summary>
	/// <param name="InArrayIndex">The index of the element we want to add to InSpellArray</param>
	/// <param name="InSpellArray">The array we want to add the prepared spell to</param>
	/// <returns>Returns true if the operation was successful</returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Load Save | Spells | Prepared Spells")
		bool TryLoadPreparedPlayerSpells(int InArrayIndex, TArray<UDA_SpellInfo*>& InSpellArray);

public:

	/// <summary>
	/// Call this when you want the save the player's game information.
	/// </summary>
	/// <param name="InSaveSlotName -">The name of the save slot you want to save to.</param>
	/// <param name="InUserIndex -">The user index of the player that this save game belongs to.</param>
	/// <param name="InPlayerName -">The player's name.</param>
	/// <param name="InPlayerCharacterTransform -">The player's character transform.</param>
	/// <param name="InPlayerControllerRotation -">The player's controller rotation.</param>
	/// <param name="InPlayerSpells -">The player's created spells.</param>
	/// <param name="InPreparedSpells -">The player's prepared spells.</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Save ")
		void SaveGame(FString InSaveSlotName, int InUserIndex, FName InPlayerName, FTransform InPlayerCharacterTransform, FRotator InPlayerControllerRotation, TArray<UDA_SpellInfo*> InPlayerSpells, TArray<UDA_SpellInfo*> InPreparedSpells);

	/// <summary>
	/// Call this when you want to load the player's saved game information.
	/// </summary>
	/// <param name="InPlayerName -">Outputs the player's name.</param>
	/// <param name="InPlayerCharacterTransform -">Outputs the player's character transform.</param>
	/// <param name="InPlayerControllerRotation -">Outputs the player's controller rotation.</param>
	/// <param name="InPlayerSpells -">Outputs the player's created spells.</param>
	/// <param name="InPreparedSpells -">Outputs the player's prepared spells</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Save Game | Load Save | Spells | Prepared Spells")
		void LoadGame(FName& InPlayerName, FTransform& InPlayerCharacterTransform, FRotator& InPlayerControllerRotation, TArray<UDA_SpellInfo*>& InPlayerSpells, TArray<UDA_SpellInfo*>& InPreparedSpells);

};
