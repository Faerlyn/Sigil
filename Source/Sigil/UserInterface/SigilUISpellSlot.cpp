


#include "SigilUISpellSlot.h"

#include "Components/Border.h"

#include "../DataAsset/UDA_SpellInfo.h"
#include "SigilSpellTooltipWidget.h"

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
	//Validate SlotSpellInfo 
	if (SlotSpellInfo)
	{
		//Set the border's image to the spell's thumbnail
		UISlotBorder->SetBrushFromTexture(SlotSpellInfo->Thumbnail);
		UISlotBorder->SetBrushColor(FLinearColor(1, 1, 1, 1));
	}
}

UWidget* USigilUISpellSlot::GetToolTipWidget()
{
	//Validate SpellTooltipWidgetBP
	if (SpellTooltipWidgetBP)
	{
		//Create a USigilSpellTooltipWidget widget
		USigilSpellTooltipWidget* SlotTooltipWidget = CreateWidget<USigilSpellTooltipWidget>(this, SpellTooltipWidgetBP);

		//Initialise the widget's properties
		SlotTooltipWidget->SetInitialVariables(SlotSpellInfo, false);

		//Return the created widget
		return SlotTooltipWidget;
	}
	
	return nullptr;
}

void USigilUISpellSlot::SetInitialVariables(UDA_SpellInfo* InSpellInfo)
{
	//Validate InSpellInfo
	if (InSpellInfo)
	{
		//Set SlotSpellInfo to InSpellInfo
		SlotSpellInfo = InSpellInfo;
	}

	//Reload the widget
	RefreshUISlot();
}
