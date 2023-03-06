

#pragma once

#include "CoreMinimal.h"
#include "SigilMenuWidgetBase.h"
#include "Components/UniformGridPanel.h"
#include "SigilUISpellSelectionSlot.h"
#include "SigilPlayerController.h"
#include "SigilCharacter.h"
#include "UDA_SpellInfo.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "SigilMenuSelectionBar.generated.h"

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

	UFUNCTION()
		void PassIndexToPlayerCharacter();

public:

	UFUNCTION(BlueprintCallable)
		void SelectNextSlot();

	UFUNCTION(BlueprintCallable)
		void SelectPreviousSlot();

	UFUNCTION(BlueprintCallable)
		void SelectSpecificSlot(int SpecificSlotIndex);

	UFUNCTION(BlueprintCallable)
		void RefreshWidgetSlots();

};
