

#pragma once

#include "CoreMinimal.h"
#include "SigilMenuWidgetBase.h"
#include "SigilMenuSelectionBar.generated.h"

class UUniformGridPanel;
class USigilUISpellSlot;
class USigilUISpellSelectionSlot;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilMenuSelectionBar : public USigilMenuWidgetBase
{
	GENERATED_BODY()
	
public:

protected:

	virtual void NativeConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UPROPERTY(EditAnywhere, Category = "Selection Bar | Reference")
		TSubclassOf<USigilUISpellSlot> SpellSelectionSlotWidgetBP;

	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* UniformGridPanel_SelectionSlots;

	UPROPERTY(VisibleAnywhere, Category = "Selection Bar | Slots")
		TArray <USigilUISpellSelectionSlot*> SelectionSlots;

	UPROPERTY(VisibleAnywhere, Category = "Selection Bar | Slots")
		USigilUISpellSelectionSlot* CurrentlySelectedSlot;

	UPROPERTY(VisibleAnywhere, Category = "Selection Bar | Slots")
		int SelectedSlotIndex = 0;

	//Sets SelectedSpellIndex on SigilCharacter's Spellcasting component to SelectedSlotIndex
	UFUNCTION()
		void PassIndexToPlayerCharacter();

public:

	//Increments SelectedSlotIndex by 1. SelectedSlotIndex will be set to 0 if it exceeds the number of elements in the SelectionSlots array.
	UFUNCTION(BlueprintCallable)
		void SelectNextSlot();

	//Decrements SelectedSlotIndex by 1. SelectedSlotIndex will be set to the last index of the SelectionSlots array if decrementing results in a value less than 0.
	UFUNCTION(BlueprintCallable)
		void SelectPreviousSlot();

	//Selects the slot at the provided index (if valid).
	UFUNCTION(BlueprintCallable)
		void SelectSpecificSlot(int SpecificSlotIndex);

	//Reloads the widget
	UFUNCTION(BlueprintCallable)
		void RefreshWidgetSlots();

};
