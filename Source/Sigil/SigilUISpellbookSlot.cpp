


#include "SigilUISpellbookSlot.h"
#include "SigilMenuSpellbook.h"


FReply USigilUISpellbookSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//If the left mouse button is being held, call the SetNewSelectedSlot function from the Spellbook widget and try to detect if the user is trying to drag the widget.
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{

		if (USigilMenuSpellbook* SpellbookWidget = Cast<USigilMenuSpellbook>(OwningWidget))
		{
			SpellbookWidget->SetNewSelectedSlot(this);
		}
		
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
