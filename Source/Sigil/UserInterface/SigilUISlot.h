

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilUISlot.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnUISlotSelected)

class USizeBox;
class UBorder;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUISlot : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// Called when a mouse button is pressed within this widget
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// Called when this widget is dragged
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		USizeBox* UISlot;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UBorder* UISlotBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient, Category = "UI Slot | Animations")
		UWidgetAnimation* Anim_SlotSelected = nullptr;

	//Tracks whether this widget is currently selected by the player
	UPROPERTY(VisibleAnywhere, Category = "UI Slot | ")
		bool bIsSelected;

	//The outline colour used when this widget is selected
	UPROPERTY(EditAnywhere, Category = "UI Slot | Outline")
		FLinearColor SelectedOutlineColour{ 1, 0.7, 0, 1};

	//The outline colour used when this widget is not selected
	UPROPERTY(EditAnywhere, Category = "UI Slot | Outline")
		FLinearColor DefaultOutlineColour{ 1, 1, 1, 1};


	//Sets the image used for UISlotBorder's brush
	virtual void SetSlotImage();

	//Getter for this widget's tooltip widget
	UFUNCTION()
		virtual UWidget* GetToolTipWidget();

	//Reloads this widget's properties
	void RefreshUISlot();

public:

	//Getter for UISlotBorder
	UFUNCTION(BlueprintCallable)
		UBorder* GetUISlotBorder();

	//Setter for bIsSelected
	//Plays animations and changes the widget's outline colour depending on the value of bIsSelected
	UFUNCTION()
		void SetIsSelected(bool NewValue);

};
