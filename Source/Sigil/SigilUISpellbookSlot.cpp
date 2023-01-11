


#include "SigilUISpellbookSlot.h"
#include "SigilMenuSpellbook.h"


FReply USigilUISpellbookSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//If the left mouse button is being held
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		//Call the SetNewSelectedSlot function from the Spellbook widget
		if (USigilMenuSpellbook* SpellbookWidget = Cast<USigilMenuSpellbook>(OwningWidget))
		{
			SpellbookWidget->SetNewSelectedSlot(this);
		}
		
		//Try to detect if the user is trying to drag the widget
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
}

void USigilUISpellbookSlot::SetInitialVariables(UDA_SpellInfo* InSpellInfo, UWidget* ParentWidget)
{
	Super::SetInitialVariables(InSpellInfo);

	if (ParentWidget)
	{
		OwningWidget = ParentWidget;
	}
}
