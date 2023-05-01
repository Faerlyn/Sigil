


#include "SigilSaveGame.h"

#include "AssetRegistry/AssetRegistryModule.h"

#include "../DataAsset/UDA_SpellInfo.h"

void USigilSaveGame::SavePlayerSpells(TArray<UDA_SpellInfo*> InPlayerSpells)
{
	//Empty the PlayerSpells array
	PlayerSpells.Empty();

	//Iterate through InPlayerSpells
	for (UDA_SpellInfo* SpellElement : InPlayerSpells)
	{
		//Add the player spells to the PlayerSpells array
		PlayerSpells.Add(SpellElement->GetSpellProperties());
	}
}

void USigilSaveGame::SavePreparedSpells(TArray<UDA_SpellInfo*> InPlayerSpells, TArray<UDA_SpellInfo*> InPreparedSpells)
{
	//Empty both the PreparedCoreSpells and PreparedPlayerSpells arrays
	PreparedCoreSpells.Empty();
	PreparedPlayerSpells.Empty();

	//Iterate through InPreparedSpells
	for (size_t i = 0; i < InPreparedSpells.Num(); ++i)
	{
		//Iterate through InPlayerSpells
		for (size_t j = 0; j < InPlayerSpells.Num(); ++j)
		{
			//If the current element of both arrays are equal
			if (InPlayerSpells[j] == InPreparedSpells[i])
			{
				//Store the indexes inside the PreparedPlayerSpells array
				PreparedPlayerSpells.Add(i, j);
			}
		}

		//If the current element's spell is not editable
		if (!InPreparedSpells[i]->bCanEdit)
		{
			//Add the element to the PreparedCoreSpells array
			PreparedCoreSpells.Add(i, InPreparedSpells[i]);
		}
	}

	//Set PreparedSpellsLength to the number of elements in the InPreparedSpells array
	PreparedSpellsLength = InPreparedSpells.Num();
}

TArray<UDA_SpellInfo*> USigilSaveGame::LoadPlayerSpells()
{
	//Iterate through PlayerSpells
	for (size_t i = 0; i < PlayerSpells.Num(); i++)
	{
		//Create a new object of type UDA_SpellInfo
		UDA_SpellInfo* CreatedSpell = NewObject<UDA_SpellInfo>(this);

		//Validate SpellMap
		if (SpellMap)
		{
			//Set CreatedSpell's SpellMap property to SpellMap
			CreatedSpell->SpellMap = SpellMap;
		}

		//Set CreatedSpell's SpellProperties using the current element
		CreatedSpell->SetSpellProperties(PlayerSpells[i]);

		//Add CreatedSpell to the OutPlayerSpells array
		OutPlayerSpells.Add(CreatedSpell);
	}

	//Return OutPlayerSpells
	return OutPlayerSpells;
}

TArray<UDA_SpellInfo*> USigilSaveGame::LoadPreparedSpells()
{
	//Create an array of type UDA_SpellInfo
	TArray<UDA_SpellInfo*> OutPreparedSpells;

	//Iterate a number of times equal to the number of elements in the PreparedSpells array when the player last saved the game
	for (size_t i = 0; i < PreparedSpellsLength; i++)
	{
		//If the prepared spell at this index was a core spell, try to load the spell and add it to OutPreparedSpells.
		if (!TryLoadPreparedCoreSpells(i, OutPreparedSpells))
		{
			//If the prepared spell at this index was a player spell, try to load the spell and add it to OutPreparedSpells.
			TryLoadPreparedPlayerSpells(i, OutPreparedSpells);
		}
	}

	//Return OutPreparedSpells
	return OutPreparedSpells;
}

bool USigilSaveGame::TryLoadPreparedCoreSpells(int InArrayIndex, TArray<UDA_SpellInfo*>& InSpellArray)
{
	//If PreparedCoreSpells has an element at the provided index
	if (PreparedCoreSpells.Find(InArrayIndex))
	{
		//Add the spell to InSpellArray at the same index
		InSpellArray.Insert(PreparedCoreSpells[InArrayIndex], InArrayIndex);
		//InSpellArray.Add(PreparedCoreSpells[InArrayIndex]);

		//Return true to show that the operation was successful
		return true;
	}
	else
	{
		//Return false to show that the operation was unsuccessful
		return false;
	}
}

bool USigilSaveGame::TryLoadPreparedPlayerSpells(int InArrayIndex, TArray<UDA_SpellInfo*>& InSpellArray)
{
	//If PreparedPlayerSpells has an element at the provided index
	if (PreparedPlayerSpells.Find(InArrayIndex))
	{
		int FoundInt = *PreparedPlayerSpells.Find(InArrayIndex);

		//Get the spell from OutPlayerSpells at the same index and add it to InSpellArray
		InSpellArray.Insert(OutPlayerSpells[FoundInt], InArrayIndex);
		//InSpellArray.Add(OutPlayerSpells[FoundInt]);

		//Return true to show that the operation was successful
		return true;
	}
	else
	{
		//Return false to show that the operation was unsuccessful
		return false;
	}
}

void USigilSaveGame::SaveGame(FString InSaveSlotName, int InUserIndex, FName InPlayerName, FTransform InPlayerCharacterTransform, FRotator InPlayerControllerRotation, TArray<UDA_SpellInfo*> InPlayerSpells, TArray<UDA_SpellInfo*> InPreparedSpells)
{
	//Save the player's save slot name, user index, player name, character transform, and controller rotation
	SaveSlotName = InSaveSlotName;
	UserIndex = InUserIndex;
	PlayerName = InPlayerName;
	PlayerCharacterTransform = InPlayerCharacterTransform;
	PlayerControllerRotation = InPlayerControllerRotation;

	//Save the player's created spells
	SavePlayerSpells(InPlayerSpells);

	//Save the player's prepared spells
	SavePreparedSpells(InPlayerSpells, InPreparedSpells);

	//Get all assets of class DA_SpellMap
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;

	//If assets of class UDA_SpellMap are discovered
	if (AssetRegistryModule.Get().GetAssetsByClass(UDA_SpellMap::StaticClass()->GetFName(), AssetData))
	{
		//Set SpellMap to the first asset of class UDA_SpellMap
		SpellMap = Cast<UDA_SpellMap>(AssetData[0].GetAsset());
	}
}

void USigilSaveGame::LoadGame(FName& InPlayerName, FTransform& InPlayerCharacterTransform, FRotator& InPlayerControllerRotation, TArray<UDA_SpellInfo*>& InPlayerSpells, TArray<UDA_SpellInfo*>& InPreparedSpells)
{
	//Output the player's name, character transform, and controller rotation
	InPlayerName = PlayerName;
	InPlayerCharacterTransform = PlayerCharacterTransform;
	InPlayerControllerRotation = PlayerControllerRotation;

	//Load the player's created spells
	InPlayerSpells = LoadPlayerSpells();

	//Load the player's prepared spells
	InPreparedSpells = LoadPreparedSpells();
}
