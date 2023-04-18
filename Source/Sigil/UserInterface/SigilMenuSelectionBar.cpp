


#include "SigilMenuSelectionBar.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "SigilUISpellSelectionSlot.h"

#include "../Actor/Character/SigilCharacter.h"
#include "../Actor/Component/SpellcastingComponent.h"
#include "../Controller/SigilPlayerController.h"
#include "../DataAsset/UDA_SpellInfo.h"

void USigilMenuSelectionBar::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshWidgetSlots();
}

bool USigilMenuSelectionBar::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//Return false if the dropped payload cannot cast to USigilUISpellSlot
	if (USigilUISpellSlot* DroppedUISlot = Cast<USigilUISpellSlot>(InOperation->Payload))
	{
		//Cast the owning player controller to ASigilPlayerController, return false if validation fails
		if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
		{
			//Add the dropped spell to the player's spellbar.
			//PC->AddSpellToSpellbar(DroppedUISlot->SlotSpellInfo);
			Cast<ASigilCharacter>(PC->GetPawn())->GetSpellcastingComponent()->AddNewPreparedSpell(DroppedUISlot->SlotSpellInfo);

			RefreshWidgetSlots();

			//Return true to show that the payload was received successfully
			return true;
		}
	}
	
	return false;
}

void USigilMenuSelectionBar::PassIndexToPlayerCharacter()
{
	//Cast the owning player controller's pawn to ASigilCharacter
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
	{
		//Validate SigilCharacter's Spellcasting component
		if (SC->GetSpellcastingComponent())
		{
			//Set SigilCharacter's selected spell index to the value of SelectedSlotIndex 
			SC->GetSpellcastingComponent()->SetSelectedSpellIndex(SelectedSlotIndex);
		}
	}
}

void USigilMenuSelectionBar::SelectNextSlot()
{
	if (!SelectionSlots.IsEmpty())
	{
		//Check if the element of SelectionSlots at SelectedSlotIndex is valid
		if (SelectionSlots[SelectedSlotIndex])
		{
			//Set IsSelected to false for that element
			SelectionSlots[SelectedSlotIndex]->SetIsSelected(false);
		}

		//If incrementing SelectedSlotIndex would result in a value greater than the length of SelectionSlots
		if ((SelectedSlotIndex + 1) > (SelectionSlots.Num() - 1))
		{
			//Set SelectedSlotIndex to 0
			SelectedSlotIndex = 0;
		}
		else
		{
			//Otherwise, increment SelectedSlotIndex
			SelectedSlotIndex++;
		}

		//Check if the element of SelectionSlots at SelectedSlotIndex is valid
		if (SelectionSlots[SelectedSlotIndex])
		{
			//Set IsSelected to true for that element
			SelectionSlots[SelectedSlotIndex]->SetIsSelected(true);

			//Pass the index to the player character
			PassIndexToPlayerCharacter();
		}
	}
}

void USigilMenuSelectionBar::SelectPreviousSlot()
{
	if (!SelectionSlots.IsEmpty())
	{
		//Check if the element of SelectionSlots at SelectedSlotIndex is valid
		if (SelectionSlots[SelectedSlotIndex])
		{
			//Set IsSelected to false for that element
			SelectionSlots[SelectedSlotIndex]->SetIsSelected(false);
		}

		//If Decrementing SelectedSlotIndex would result in a value less than zero
		if ((SelectedSlotIndex - 1) < 0)
		{
			//Set SelectedSlotIndex to the last index of the array
			SelectedSlotIndex = SelectionSlots.Num() - 1;
		}
		else
		{
			//Otherwise, decrement SelectedSlotIndex
			SelectedSlotIndex--;
		}

		//Check if the element of SelectionSlots at SelectedSlotIndex is valid
		if (SelectionSlots[SelectedSlotIndex])
		{
			//Set IsSelected to true for that element
			SelectionSlots[SelectedSlotIndex]->SetIsSelected(true);

			//Pass the index to the player character
			PassIndexToPlayerCharacter();
		}
	}
}

void USigilMenuSelectionBar::SelectSpecificSlot(int SpecificSlotIndex)
{
	if (!SelectionSlots.IsEmpty())
	{
		//Check if the provided index is valid
		if (SpecificSlotIndex >= 0 && SpecificSlotIndex <= SelectionSlots.Num()-1)
		{
			//If SpecificSlotIndex and SelectedSlotIndex are not equal
			if (SpecificSlotIndex != SelectedSlotIndex)
			{
				//Check if the element of SelectionSlots at SelectedSlotIndex is valid
				if (SelectionSlots[SelectedSlotIndex])
				{
					//Set IsSelected to false for that element
					SelectionSlots[SelectedSlotIndex]->SetIsSelected(false);
				}

				//Check if the element of SelectionSlots at SpecificSlotIndex is valid
				if (SelectionSlots[SpecificSlotIndex])
				{
					//Set IsSelected to true for that element
					SelectionSlots[SpecificSlotIndex]->SetIsSelected(true);

					//Set SelectedSlotIndex to SpecificSlotIndex
					SelectedSlotIndex = SpecificSlotIndex;

					//Pass the index to the player character
					PassIndexToPlayerCharacter();
				}
			}
		}
	}
}

void USigilMenuSelectionBar::RefreshWidgetSlots()
{
	//Validate UniformGridPanel_SelectionSlots
	if (UniformGridPanel_SelectionSlots)
	{
		//Clear any child widgets from the grid panel
		UniformGridPanel_SelectionSlots->ClearChildren();
	}

	//Clear the SelectionsSlots array
	SelectionSlots.Empty();

	//Cast the owning player controller's pawn to ASigilCharacter
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
	{

		TArray<UDA_SpellInfo*> PreparedSpellsArray = SC->GetSpellcastingComponent()->GetPreparedSpells();

		//If the PreparedSpells array is not empty
		if (!PreparedSpellsArray.IsEmpty())
		{
			//For each elements of the PreparedSpells array
			for (UDA_SpellInfo* SpellInfo : PreparedSpellsArray)
			{
				int ArrayIndex = PreparedSpellsArray.IndexOfByKey(SpellInfo);

				//Create the name of the widget using the following format: SelectionSlot_[ArrayIndex]_[SpellInfo->Name] e.g. SelectionSlot_1_Fireball
				FString SlotName = "SelectionSlot_";
				SlotName.Append(UKismetStringLibrary::Conv_IntToString(ArrayIndex));
				SlotName.Append("_");
				SlotName.Append(UKismetStringLibrary::Conv_NameToString(SpellInfo->Name));

				//Create a SpellSelectionSlot widget
				if (USigilUISpellSelectionSlot* SpellSelectionSlot = CreateWidget<USigilUISpellSelectionSlot>(this, SpellSelectionSlotWidgetBP, UKismetStringLibrary::Conv_StringToName(SlotName)))
				{
					//Call SetInitialVariables for the newly created SpellSelectionSlot
					SpellSelectionSlot->SetInitialVariables(SpellInfo, ArrayIndex);

					//Add the widget to the SelectionsSlots array
					SelectionSlots.Add(SpellSelectionSlot);

					//Validate UniformGridPanel_SelectionSlots
					if (UniformGridPanel_SelectionSlots)
					{
						//Make the new widget a child of the grid panel
						UniformGridPanel_SelectionSlots->AddChildToUniformGrid(SpellSelectionSlot, 0, ArrayIndex);
					}
				}
			}
		}
	}

	//Clamp SelectedSlotIndex to prevent errors from occuring when Slots are removed (such as when a player drags a spell off of their spellbar)
	SelectedSlotIndex = UKismetMathLibrary::Clamp(SelectedSlotIndex, 0, SelectionSlots.Num() - 1);

	//If SelectionSlots is not empty
	if (!SelectionSlots.IsEmpty())
	{
		//Set IsSelected to true for the element at SelectedSlotIndex
		SelectionSlots[SelectedSlotIndex]->SetIsSelected(true);

		//Pass the index to the player character
		PassIndexToPlayerCharacter();
	}
}
