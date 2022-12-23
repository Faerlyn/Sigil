


#include "SigilUISpellSelectionSlot.h"

void USigilUISpellSelectionSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void USigilUISpellSelectionSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		PC->RemoveSpellFromSpellbar(SlotSpellInfo);
	}
}

void USigilUISpellSelectionSlot::SetInitialVariables(UDA_SpellInfo* InSpellInfo, int inSlotHotkey)
{
	Super::SetInitialVariables(InSpellInfo);

	SlotHotkey = inSlotHotkey;

	SlotHotkey_Text->Text = UKismetTextLibrary::Conv_IntToText(SlotHotkey);
}
