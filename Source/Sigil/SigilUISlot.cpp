


#include "SigilUISlot.h"

void USigilUISlot::NativePreConstruct()
{
	Super::NativeConstruct();

}

void USigilUISlot::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshUISlot();


}

FReply USigilUISlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//If the left mouse button is being held, try to detect if the user is trying to drag the widget.
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	else
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
}

void USigilUISlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//Create a drag drop operation with this widget as its payload
	UDragDropOperation* SlotDragDrop = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	SlotDragDrop->Payload = this;
	SlotDragDrop->DefaultDragVisual = this;
	SlotDragDrop->Pivot = EDragPivot::TopLeft;
	SlotDragDrop->Offset = FVector2D(0.1f, 0.1f);

	OutOperation = SlotDragDrop;

}

void USigilUISlot::SetSlotImage()
{
}

UWidget* USigilUISlot::GetToolTipWidget()
{
	return nullptr;
}

void USigilUISlot::RefreshUISlot()
{
	SetSlotImage();
	ToolTipWidgetDelegate.BindDynamic(this, &USigilUISlot::GetToolTipWidget);
	SynchronizeProperties();
}

void USigilUISlot::SetIsSelected(bool NewValue)
{
	//If NewValue (boolean input) is not the same as bIsSelected 
	if (NewValue != bIsSelected)
	{
		//Set bIsSelected to the value of NewValue
		bIsSelected = NewValue;
	}

	//If bIsSelected is true
	if (bIsSelected)
	{
		//Set the colour of the widget's outline to SelectedOutlineColour
		UISlotBorder->Background.OutlineSettings.Color = SelectedOutlineColour;

		//Play the SlotSelected animation
		PlayAnimation(Anim_SlotSelected, 0, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
	}
	else
	{
		//If it is false, set the outline to DefaultOutlineColour
		UISlotBorder->Background.OutlineSettings.Color = DefaultOutlineColour;

		//Play the SlotSelected animation in reverse
		PlayAnimation(Anim_SlotSelected, 0, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
	}
}