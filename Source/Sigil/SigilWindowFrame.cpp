


#include "SigilWindowFrame.h"

void USigilWindowFrame::NativePreConstruct()
{
	Super::NativePreConstruct();

	//Create the Window Content widget and set the reference variable
	if (WindowContent)
	{
		WindowContentWidget = Cast<USigilMenuWidgetBase>(CreateWidget(GetOwningPlayer(), WindowContent));

		//Add the created widget to the named slot as a child
		NamedSlot_WindowContent->AddChild(WindowContentWidget);

		//Get the created widget's name and set it as the name of the window
		FText NewWindowName = WindowContentWidget->GetWidgetName();
		WindowName = NewWindowName;
	}

}

void USigilWindowFrame::NativeConstruct()
{
	Super::NativeConstruct();

	Border_WindowTitleBar->OnMouseButtonDownEvent.BindUFunction(this, "WindowTitleBar_OnMouseButtonDownEvent");
	Border_WindowTitleBar->OnMouseButtonUpEvent.BindUFunction(this, "WindowTitleBar_OnMouseButtonUpEvent");

	Border_ResizeEast->OnMouseButtonDownEvent.BindUFunction(this, "Border_ResizeEast_OnMouseButtonDownEvent");
	Border_ResizeEast->OnMouseButtonUpEvent.BindUFunction(this, "Border_ResizeEast_OnMouseButtonUpEvent");

	Border_ResizeSouth->OnMouseButtonDownEvent.BindUFunction(this, "Border_ResizeSouth_OnMouseButtonDownEvent");
	Border_ResizeSouth->OnMouseButtonUpEvent.BindUFunction(this, "Border_ResizeSouth_OnMouseButtonUpEvent");

	Border_ResizeSouthEast->OnMouseButtonDownEvent.BindUFunction(this, "Border_ResizeSouthEast_OnMouseButtonDownEvent");
	Border_ResizeSouthEast->OnMouseButtonUpEvent.BindUFunction(this, "Border_ResizeSouthEast_OnMouseButtonUpEvent");

	Button_CloseWindow->OnClicked.AddDynamic(this, &USigilWindowFrame::OnClicked_Button_CloseWindow);

	SetMinimumDesiredSize();
	ResizeWindowToMinimum();
}

void USigilWindowFrame::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//If window is moveable, update its location. If not then stop updating.
	if (bWindowIsMoveable) { UpdateWidgetLocation(); }

	//If the window is resizable, call the resize window function
	if (bWindowIsResizeable) {ResizeWindow(); }

}

void USigilWindowFrame::SetWindowIsMoveable(bool InBool)
{
	//Set bWindowIsResizeable to InBool
	bWindowIsMoveable = InBool;

	//Print to the output log
	UE_LOG(LogTemp, Display, TEXT("bWindowIsMoveable set to %s"), (bWindowIsMoveable ? TEXT("true") : TEXT("false")));
}

void USigilWindowFrame::SetWindowIsResizeable(bool InBool)
{
	//Set bWindowIsResizeable to InBool
	bWindowIsResizeable = InBool;

	//Print to the output log
	UE_LOG(LogTemp, Display, TEXT("bWindowIsResizeable set to %s"), (bWindowIsResizeable ? TEXT("true") : TEXT("false")));
}

void USigilWindowFrame::SetWindowIsResizeableLeftRightOnly(bool InBool)
{
	//Set bWindowIsResizeable to InBool
	bWindowIsResizeableLeftRightOnly = InBool;

	//Print to the output log
	UE_LOG(LogTemp, Display, TEXT("bWindowIsResizeableLeftRightOnly set to %s"), (bWindowIsResizeableLeftRightOnly ? TEXT("true") : TEXT("false")));
}

void USigilWindowFrame::SetWindowIsResizeableUpDownOnly(bool InBool)
{
	//Set bWindowIsResizeable to InBool
	bWindowIsResizeableUpDownOnly = InBool;

	//Print to the output log
	UE_LOG(LogTemp, Display, TEXT("bWindowIsResizeableUpDownOnly set to %s"), (bWindowIsResizeableUpDownOnly ? TEXT("true") : TEXT("false")));
}

FReply USigilWindowFrame::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//Does nothing, this function exists to consume the mouse input when the user clicks on the widget
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply USigilWindowFrame::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//If any held mouse button is released, call the ReleaseWidget function
	ReleaseWidget(InMouseEvent);
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void USigilWindowFrame::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	//Let go of the widget when the mouse has left
	ReleaseWidget(InMouseEvent);
}

FEventReply USigilWindowFrame::WindowTitleBar_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//Check if the left mouse button is held down
	if (UKismetInputLibrary::PointerEvent_IsMouseButtonDown(MouseEvent, EKeys::LeftMouseButton))
	{
		//Set bWindowIsMoveable to true
		SetWindowIsMoveable(true);

		//Get the position of the widget and subtract it from the mouse's position on the viewport, set MousePosDifference to the result.
		MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
		MousePosDifference = MousePos - UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowFrame)->GetPosition();

		return FEventReply(true);
	}

	return FEventReply(false);
}

FEventReply USigilWindowFrame::WindowTitleBar_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//If any held mouse button is released, call the ReleaseWidget function
	ReleaseWidget(MouseEvent);

	return FEventReply(true);
}

void USigilWindowFrame::OnClicked_Button_CloseWindow()
{
	//Remove the widget when the close button is clicked
	if (ASigilPlayerController* SigilPlayerController = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		SigilPlayerController->TogglePlayerMouseCursor(false);
	}

	RemoveFromParent();
}

void USigilWindowFrame::SetWindowFramePosition(FVector2D NewPosition)
{
	//Slot WindowFrame as a Canvas Slot and set its position to NewPosition
	UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowFrame)->SetPosition(NewPosition);
}

void USigilWindowFrame::GetNewWindowSize()
{
	//Get the widget's current position
	FVector2D WindowPosition = UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowFrame)->GetPosition();

	//Get the mouse's current position
	MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	FVector2D bump(1,1);

	//NewWindowSize = (MousePosition + 1) - WindowPosition
	NewWindowSize = (MousePos + bump) - WindowPosition;
}

void USigilWindowFrame::ResizeWindow()
{
	GetNewWindowSize();

	//Get WindowFrame's current size and store it, split NewWindowSize into two local float variables
	CurrentWindowSize = UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowFrame)->GetSize();

	float NewWindowSizeX = NewWindowSize.X;
	float NewWindowSizeY = NewWindowSize.Y;

	//If WindowIsResizeableLeftRightOnly is true, make NewWindowSizeY equal CurrentWindowSize.Y
	if (bWindowIsResizeableLeftRightOnly)
	{
		NewWindowSizeY = CurrentWindowSize.Y;
	}
	//If WindowIsResizeableUpDownOnly is true, make NewWindowSizeX equal CurrentWindowSize.X
	else if (bWindowIsResizeableUpDownOnly)
	{
		NewWindowSizeX = CurrentWindowSize.X;
	}

	//Clamp the X and Y value of NewWindowSize according to WindowFrame's Min & Max Desired Width & Height
	NewWindowSize.Set(UKismetMathLibrary::Clamp(NewWindowSizeX, WindowFrame->MinDesiredWidth, WindowFrame->MaxDesiredWidth),
					  UKismetMathLibrary::Clamp(NewWindowSizeY, WindowFrame->MinDesiredHeight, WindowFrame->MaxDesiredHeight));

	//Set the size of WindowFrame to NewWindowSize, print this value to the output log and screen
	UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowFrame)->SetSize(NewWindowSize);

	UE_LOG(LogTemp, Display, TEXT("New Window Size: %s"), *NewWindowSize.ToString());
}

void USigilWindowFrame::ResizeWindowToMinimum()
{
	//Set the size of the widget its minimum desired width and height
	UWidgetLayoutLibrary::SlotAsCanvasSlot(WindowFrame)->SetSize(UKismetMathLibrary::MakeVector2D(WindowFrame->MinDesiredWidth, WindowFrame->MinDesiredHeight));
}

FEventReply USigilWindowFrame::Border_ResizeEast_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//Set bWindowIsResizeable to true
	SetWindowIsResizeable(true);

	//Set bWindowIsResizeableLeftRightOnly to true
	SetWindowIsResizeableLeftRightOnly(true);
	
	return FEventReply(true);
}

FEventReply USigilWindowFrame::Border_ResizeEast_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//If the left mouse button is not being held down, set bWindowIsResizable and bWindowIsResizableLeftRightOnly to false
	if (!UKismetInputLibrary::PointerEvent_IsMouseButtonDown(MouseEvent, EKeys::LeftMouseButton))
	{
		SetWindowIsResizeable(false);
		SetWindowIsResizeableLeftRightOnly(false);

		return FEventReply(true);
	}
	
	return FEventReply(false);
}

FEventReply USigilWindowFrame::Border_ResizeSouth_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//Set bWindowIsResizeable to true
	SetWindowIsResizeable(true);

	//Set bWindowIsResizeableUpDownOnly to true
	SetWindowIsResizeableUpDownOnly(true);

	return FEventReply(true);
}

FEventReply USigilWindowFrame::Border_ResizeSouth_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//If the left mouse button is not being held down, set bWindowIsResizable and bWindowIsResizableUpDownOnly to false
	if (!UKismetInputLibrary::PointerEvent_IsMouseButtonDown(MouseEvent, EKeys::LeftMouseButton))
	{
		SetWindowIsResizeable(false);
		SetWindowIsResizeableUpDownOnly(false);

		return FEventReply(true);
	}

	return FEventReply(false);
}

FEventReply USigilWindowFrame::Border_ResizeSouthEast_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//Set bWindowIsResizeable to true
	SetWindowIsResizeable(true);

	return FEventReply(true);
}

FEventReply USigilWindowFrame::Border_ResizeSouthEast_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	//If the left mouse button is not being held down, set bWindowIsResizable to false
	if (!UKismetInputLibrary::PointerEvent_IsMouseButtonDown(MouseEvent, EKeys::LeftMouseButton))
	{
		SetWindowIsResizeable(false);

		return FEventReply(true);
	}

	return FEventReply(false);
}

FText USigilWindowFrame::Get_TextBlock_WindowTitle_Text()
{
	return WindowName;
}

void USigilWindowFrame::ReleaseWidget(const FPointerEvent& MouseEvent)
{
	//If the left mouse button is not currently held down, stop moving or resizing the window
	if (!UKismetInputLibrary::PointerEvent_IsMouseButtonDown(MouseEvent, EKeys::LeftMouseButton))
	{
		if (bWindowIsMoveable) {SetWindowIsMoveable(false); }
		if (bWindowIsResizeable) {SetWindowIsResizeable(false); }
		if (bWindowIsResizeableLeftRightOnly) {SetWindowIsResizeableLeftRightOnly(false); }
		if (bWindowIsResizeableUpDownOnly) {SetWindowIsResizeableUpDownOnly(false); }
	}
}

bool USigilWindowFrame::ToggleIsInViewPort()
{
	//If the widget is in the viewport, remove it. If not, add it to the player's screen.
	if (this->IsInViewport())
	{
		this->RemoveFromViewport();
		return false;
	}
	else
	{
		return this->AddToPlayerScreen();
	}
}

void USigilWindowFrame::SetMinimumDesiredSize()
{
	if (WindowContentWidget)
	{
		//Get the minimum width and height from the Window Content Widget. Add these values to the minimum desired height and width of WindowFrame
		WindowFrame->SetMinDesiredWidth(WindowFrame->MinDesiredWidth + WindowContentWidget->WidgetMinimumWidth);
		WindowFrame->SetMinDesiredHeight(WindowFrame->MinDesiredHeight + WindowContentWidget->WidgetMinimumHeight);
	}
}

void USigilWindowFrame::UpdateWidgetLocation()
{
	//Get the mouse's position on the viewport
	MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);

	//WindowFrame position = MousePos - MousePosDifference
	SetWindowFramePosition(MousePos - MousePosDifference);
}
