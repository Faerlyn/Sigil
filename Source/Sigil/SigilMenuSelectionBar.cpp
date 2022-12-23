


#include "SigilMenuSelectionBar.h"

void USigilMenuSelectionBar::NativePreConstruct()
{
	Super::NativePreConstruct();


}

void USigilMenuSelectionBar::NativeConstruct()
{
	Super::NativeConstruct();

	SelectedSlotIndex = 0;

	RefreshWidgetSlots();
}

bool USigilMenuSelectionBar::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//Return false if the dropped payload cannot cast to USigilUISpellSlot
	if (USigilUISpellSlot* DroppedUISlot = Cast<USigilUISpellSlot>(InOperation->Payload))
	{
		//Get the player controller and add the dropped spell to the selection bar. Return false if any validation checks fail.
		if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
		{
			PC->AddSpellToSpellbar(DroppedUISlot->SlotSpellInfo);
			return true;
		}
	}
	
	return false;
}

void USigilMenuSelectionBar::PassIndexToPlayerCharacter()
{
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
	{
		SC->SetSelectedSpellIndex(SelectedSlotIndex);
	}
}

void USigilMenuSelectionBar::SelectNextSlot()
{
	//Get the SelectionSlot at the currently selected index and set IsSelected to false
	if (SelectionSlots[SelectedSlotIndex])
	{
		SelectionSlots[SelectedSlotIndex]->SetIsSelected(false);
	}

	//Increment SelectedSlotIndex by 1. If the new value is greater than the length of SelectionSlots, set SelectedSlotIndes to 0
	if ((SelectedSlotIndex + 1) > (SelectionSlots.Num() - 1))
	{
		SelectedSlotIndex = 0;
	}
	else
	{
		SelectedSlotIndex++;
	}

	//Get a reference to the element at SelectedSlotIndex, validate it. Set IsSelected to true and pass the index to the player character
	if (SelectionSlots[SelectedSlotIndex])
	{
		SelectionSlots[SelectedSlotIndex]->SetIsSelected(true);

		PassIndexToPlayerCharacter();
	}
}

void USigilMenuSelectionBar::SelectPreviousSlot()
{
	//Get the SelectionSlot at the currently selected index and set IsSelected to false
	if (SelectionSlots[SelectedSlotIndex])
	{
		SelectionSlots[SelectedSlotIndex]->SetIsSelected(false);
	}

	//Increment SelectedSlotIndex by 1. If the new value is greater than the length of SelectionSlots, set SelectedSlotIndes to 0
	if ((SelectedSlotIndex - 1) < 0)
	{
		SelectedSlotIndex = SelectionSlots.Num() - 1;
	}
	else
	{
		SelectedSlotIndex--;
	}

	//Get a reference to the element at SelectedSlotIndex, validate it. Set IsSelected to true and pass the index to the player character
	if (SelectionSlots[SelectedSlotIndex])
	{
		SelectionSlots[SelectedSlotIndex]->SetIsSelected(true);

		PassIndexToPlayerCharacter();
	}
}

void USigilMenuSelectionBar::RefreshWidgetSlots()
{
	//Clear any child widgets from the grid panel, clear the SelectionsSlots array
	if (UniformGridPanel_SelectionSlots)
	{
		UniformGridPanel_SelectionSlots->ClearChildren();
	}

	SelectionSlots.Empty();

	//Get the owning controller's controlled pawn, cast it to BP_SigilCharacter and check that the PreparedSpells array is not empty
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
	{
		TArray<UDA_SpellInfo*> PreparedSpellsArray = SC->SpellcastingComponent->PreparedSpells;

		if (!PreparedSpellsArray.IsEmpty())
		{
			//For each elements of the PreparedSpells array, create a SpellSelectionSlotWidget. Add the widget to the SelectionsSlots array then make it a child of the grid panel
			for (UDA_SpellInfo* SpellInfo : PreparedSpellsArray)
			{
				int ArrayIndex = PreparedSpellsArray.IndexOfByKey(SpellInfo);

				FString SlotName = "SelectionSlot_";
				SlotName.Append(UKismetStringLibrary::Conv_IntToString(ArrayIndex));
				SlotName.Append("_");
				SlotName.Append(UKismetStringLibrary::Conv_NameToString(SpellInfo->Name));

				if (USigilUISpellSelectionSlot* SpellSelectionSlot = CreateWidget<USigilUISpellSelectionSlot>(this, SpellSelectionSlotWidgetBP, UKismetStringLibrary::Conv_StringToName(SlotName)))
				{
					SpellSelectionSlot->SetInitialVariables(SpellInfo, ArrayIndex);

					SelectionSlots.Add(SpellSelectionSlot);

					if (UniformGridPanel_SelectionSlots)
					{
						UniformGridPanel_SelectionSlots->AddChildToUniformGrid(SpellSelectionSlot, 0, ArrayIndex);
					}
				}
			}
		}
	}

	//Once all slots have been created, set the first element as the selected spell and have the player equip it
	if (!SelectionSlots.IsEmpty())
	{
		SelectionSlots[SelectedSlotIndex]->SetIsSelected(true);

		PassIndexToPlayerCharacter();
	}
}
