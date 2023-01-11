


#include "SigilUISpellSelectionSlot.h"

void USigilUISpellSelectionSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsSelected(false);
}

void USigilUISpellSelectionSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	//When this widget is dragged
	if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		//Remove it from the player's spellbar
		PC->RemoveSpellFromSpellbar(SlotSpellInfo);

		//Set bIsSelected to false
		SetIsSelected(false);
	}
}

void USigilUISpellSelectionSlot::SetInitialVariables(UDA_SpellInfo* InSpellInfo, int inSlotHotkey)
{
	Super::SetInitialVariables(InSpellInfo);

	SlotHotkey = inSlotHotkey;

	SlotHotkey_Text->Text = UKismetTextLibrary::Conv_IntToText(SlotHotkey);
}
