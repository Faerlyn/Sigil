

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/NamedSlot.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "SigilMenuWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SigilPlayerController.h"
#include "SigilWindowFrame.generated.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mouse | ")
		FVector2D MousePosDifference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mouse | ")
		FVector2D MousePos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Move | ")
		bool bWindowIsMoveable;

	UFUNCTION()
		void SetWindowIsMoveable(bool InBool);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Move | ")
		FVector2D WindowOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Resize | ")
		FVector2D CurrentWindowSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Resize | ")
		FVector2D NewWindowSize;

public:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Resize | ")
		UBorder* Border_ResizeEast;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Resize | ")
		UBorder* Border_ResizeSouth;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Resize | ")
		UBorder* Border_ResizeSouthEast;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Frame | ")
		UBorder* Border_WindowFrame;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Frame | ")
		UBorder* Border_WindowTitleBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Frame | ")
		UButton* Button_CloseWindow;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Frame | ")
		UNamedSlot* NamedSlot_WindowContent;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Frame | ")
		UTextBlock* TextBlock_WindowTitle;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Window Frame | ")
		USizeBox* WindowFrame;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Window Frame | ")
		TSubclassOf<USigilMenuWidgetBase> WindowContent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Resize | ")
		bool bWindowIsResizeable;

	UFUNCTION()
		void SetWindowIsResizeable(bool InBool);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Resize | ")
		bool bWindowIsResizeableLeftRightOnly;

	UFUNCTION()
		void SetWindowIsResizeableLeftRightOnly(bool InBool);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Resize | ")
		bool bWindowIsResizeableUpDownOnly;

	UFUNCTION()
		void SetWindowIsResizeableUpDownOnly(bool InBool);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Frame | ")
		FText WindowName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Window Frame | ")
		USigilMenuWidgetBase* WindowContentWidget;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION(Category = "Window Move | ")
		FEventReply WindowTitleBar_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Move | ")
		FEventReply WindowTitleBar_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Move | ")
		void OnClicked_Button_CloseWindow();

	UFUNCTION(Category = "Window Move | ")
		void SetWindowFramePosition(FVector2D NewPosition);

	UFUNCTION(Category = "Window Resize | ")
		void GetNewWindowSize();

	UFUNCTION(Category = "Window Resize | ")
		void ResizeWindow();

	UFUNCTION(Category = "Window Resize | ")
		void ResizeWindowToMinimum();

	UFUNCTION(Category = "Window Resize | ")
		FEventReply Border_ResizeEast_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Resize | ")
		FEventReply Border_ResizeEast_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Resize | ")
		FEventReply Border_ResizeSouth_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Resize | ")
		FEventReply Border_ResizeSouth_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Resize | ")
		FEventReply Border_ResizeSouthEast_OnMouseButtonDownEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Resize | ")
		FEventReply Border_ResizeSouthEast_OnMouseButtonUpEvent(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UFUNCTION(Category = "Window Frame | ")
		FText Get_TextBlock_WindowTitle_Text();

	UFUNCTION(BlueprintCallable, Category = "Window Frame | ")
		void ReleaseWidget(const FPointerEvent& MouseEvent);

	UFUNCTION(BlueprintCallable, Category = "Window Frame | ")
		bool ToggleIsInViewPort();

	UFUNCTION(Category = "Window Frame | ")
		void SetMinimumDesiredSize();

	UFUNCTION( Category = "Window Move | ")
		void UpdateWidgetLocation();
};
