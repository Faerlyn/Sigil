

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilWindowFrame.generated.h"

class UBorder;
class UButton;
class UNamedSlot;
class USizeBox;
class UTextBlock;

class USigilMenuWidgetBase;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilWindowFrame : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	//The position of the mouse cursor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Mouse | ")
		FVector2D MousePos;

	//The position of the mouse cursor relative to the position of the window
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Mouse | ")
		FVector2D MousePosDifference;

	//Can the window be moved?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Window Move | ")
		bool bWindowIsMoveable;

	//The window's current size
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Window Resize | ")
		FVector2D CurrentWindowSize;

	//The window's new size
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Window Resize | ")
		FVector2D NewWindowSize;

	//Can the window be resized?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Window Resize | ")
		bool bWindowIsResizeable;

	//Can the window's width be changed?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Window Resize | ")
		bool bWindowIsResizeableLeftRightOnly;

	//Can the window's height be changed?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | Window Resize | ")
		bool bWindowIsResizeableUpDownOnly;

	//The name of this window
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | ")
		FText WindowName;

	//A reference to the blueprint of the window's contents.
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Sigil Window Frame | ")
		TSubclassOf<USigilMenuWidgetBase> WindowContent;

	//A reference to the window's contents (e.g. Spellbook widget).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Window Frame | ")
		USigilMenuWidgetBase* WindowContentWidget;

	//Holds the contents of the window (e.g. Spellbook widget).
	UPROPERTY(meta = (BindWidget))
		UNamedSlot* NamedSlot_WindowContent;

	//The parent of this widget's other components
	UPROPERTY(meta = (BindWidget))
		USizeBox* WindowFrame;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border_WindowFrame;

	//The window's title bar
	UPROPERTY(meta = (BindWidget))
		UBorder* Border_WindowTitleBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_WindowTitle;

	UPROPERTY(meta = (BindWidget))
		UButton* Button_CloseWindow;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border_ResizeEast;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border_ResizeSouth;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border_ResizeSouthEast;

	//Setter for bWindowIsMoveable
	UFUNCTION()
		void SetWindowIsMoveable(bool InBool);

	//Setter for bWindowIsResizeable
	UFUNCTION()
		void SetWindowIsResizeable(bool InBool);

	//Setter for bWindowIsResizeableLeftRightOnly
	UFUNCTION()
		void SetWindowIsResizeableLeftRightOnly(bool InBool);

	//Setter for bWindowIsResizeableUpDownOnly
	UFUNCTION()
		void SetWindowIsResizeableUpDownOnly(bool InBool);

	//Called when a mouse button is pressed within Border_WindowTitleBar
	UFUNCTION(Category = "Sigil Window Frame | Window Move | ")
		FEventReply WindowTitleBar_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when a mouse button is released within Border_WindowTitleBar
	UFUNCTION(Category = "Sigil Window Frame | Window Move | ")
		FEventReply WindowTitleBar_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when Button_CloseWindow is clicked
	UFUNCTION(Category = "Sigil Window Frame | Window Move | ")
		void OnClicked_Button_CloseWindow();

	//Sets this widget's position
	UFUNCTION(Category = "Sigil Window Frame | Window Move | ")
		void SetWindowFramePosition(FVector2D NewPosition);

	//Gets the window's new size by getting the difference between the mouse cursor's position and the postion of the window.
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		void GetNewWindowSize();

	//Sets the window's new size so long as the window is currently resizeable
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		void ResizeWindow();

	//Sets the size of the window to its minimum desired width and height
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		void ResizeWindowToMinimum();

	//Called when TextBlock_WindowTitle's TextDelegate is executed
	UFUNCTION(Category = "Sigil Window Frame | ")
		FText Get_TextBlock_WindowTitle_Text();

	//Sets the window's minimum desired width and height
	UFUNCTION(Category = "Sigil Window Frame | ")
		void SetMinimumDesiredSize();

	//Updates the widget's position using the mouse cursor's current position on the viewport.
	UFUNCTION(Category = "Sigil Window Frame | Window Move | ")
		void UpdateWidgetPosition();

	//Called when a mouse button is pressed within Border_ResizeEast
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		FEventReply Border_ResizeEast_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when a mouse button is released within Border_ResizeEast
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		FEventReply Border_ResizeEast_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when a mouse button is pressed within Border_ResizeSouth
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		FEventReply Border_ResizeSouth_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when a mouse button is released within Border_ResizeSouth
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		FEventReply Border_ResizeSouth_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when a mouse button is pressed within Border_ResizeSouthEast
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		FEventReply Border_ResizeSouthEast_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	//Called when a mouse button is released within Border_ResizeSouthEast
	UFUNCTION(Category = "Sigil Window Frame | Window Resize | ")
		FEventReply Border_ResizeSouthEast_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);


public:

	//Setter for WindowContent
	UFUNCTION()
		void SetWindowContent(TSubclassOf<USigilMenuWidgetBase> InWindowContent);

	//Toggles between adding the window to the player screen and removing it.
	UFUNCTION(BlueprintCallable, Category = "Sigil Window Frame | ")
		bool ToggleIsInViewPort();

	//Called when the left mouse button is released/not held down.
	//Stops the window from being moved or resized.
	UFUNCTION(BlueprintCallable, Category = "Sigil Window Frame | ")
		void ReleaseWidget(const FPointerEvent& MouseEvent);

};
