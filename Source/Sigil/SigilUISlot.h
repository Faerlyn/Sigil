

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UDA_SpellInfo.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SigilUISlot.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnUISlotSelected)

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUISlot : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
		void SetIsSelected(bool NewValue);

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UBorder* UISlotBorder;

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void SetSlotImage();

	UFUNCTION(BlueprintCallable)
	virtual UWidget* GetToolTipWidget();

	void RefreshUISlot();

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient, Category = "UI Slot | Animations")
		UWidgetAnimation* Anim_SlotSelected = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "UI Slot | ")
		bool bIsSelected;

	UPROPERTY(EditAnywhere, Category = "UI Slot | Outline")
		FLinearColor SelectedOutlineColour{ 1, 0.7, 0, 1};

	UPROPERTY(EditAnywhere, Category = "UI Slot | Outline")
		FLinearColor DefaultOutlineColour{ 1, 1, 1, 1};

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		USizeBox* UISlot;

	

};
