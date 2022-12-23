


#include "SigilUISpellSlot.h"

void USigilUISpellSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void USigilUISpellSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

void USigilUISpellSlot::SetSlotImage()
{
	//If SlotSpellInfo is valid, set the border's image to the spell's thumbnail
	if (SlotSpellInfo)
	{
		UISlotBorder->SetBrushFromTexture(SlotSpellInfo->Thumbnail);
		UISlotBorder->SetBrushColor(FLinearColor(1, 1, 1, 1));
	}
}

UWidget* USigilUISpellSlot::GetToolTipWidget()
{
	if (SpellTooltipWidgetBP)
	{
		USigilSpellTooltipWidget* SlotTooltipWidget = CreateWidget<USigilSpellTooltipWidget>(this, SpellTooltipWidgetBP);
		SlotTooltipWidget->SetInitialVariables(SlotSpellInfo, false);

		return SlotTooltipWidget;
	}
	
	return nullptr;
}

void USigilUISpellSlot::SetInitialVariables(UDA_SpellInfo* InSpellInfo)
{
	if (InSpellInfo)
	{
		SlotSpellInfo = InSpellInfo;
	}

	RefreshUISlot();
}
