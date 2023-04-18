


#include "SigilUISpellbookSlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#include "../Controller/SigilPlayerController.h"
#include "SigilMenuSpellbook.h"


FReply USigilUISpellbookSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//If the left mouse button is being held
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		//Cast Owning Widget to USigilMenuSpellbook and validate it
		if (USigilMenuSpellbook* SpellbookWidget = Cast<USigilMenuSpellbook>(OwningWidget))
		{
			//Call the SetNewSelectedSlot function from the Spellbook widget and set this widget as the new selected slot
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
	
	//Validate ParentWidget
	if (ParentWidget)
	{
		//Set OwningWidget to ParentWidget
		OwningWidget = ParentWidget;
	}
}
