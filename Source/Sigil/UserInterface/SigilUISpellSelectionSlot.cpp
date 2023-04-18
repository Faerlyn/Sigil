


#include "SigilUISpellSelectionSlot.h"

#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

#include "../Actor/Character/SigilCharacter.h"
#include "../Actor/Component/SpellcastingComponent.h"
#include "../Controller/SigilPlayerController.h"

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
		//PC->RemoveSpellFromSpellbar(SlotSpellInfo);
		Cast<ASigilCharacter>(PC->GetPawn())->GetSpellcastingComponent()->RemovePreparedSpell(SlotSpellInfo);

		PC->RequestRefreshSpellBar();

		//Set bIsSelected to false
		SetIsSelected(false);
	}
}

void USigilUISpellSelectionSlot::SetInitialVariables(UDA_SpellInfo* InSpellInfo, int inSlotHotkey)
{
	Super::SetInitialVariables(InSpellInfo);

	//Set SlotHotkey to inSlotHotkey +1
	SlotHotkey = inSlotHotkey + 1;
	
	//Validate SlotHotkey_Text
	if (SlotHotkey_Text)
	{
		//Set SlotHotkey_Text's text value to SlotHotkey
		SlotHotkey_Text->Text = UKismetTextLibrary::Conv_IntToText(SlotHotkey);
	}
}
