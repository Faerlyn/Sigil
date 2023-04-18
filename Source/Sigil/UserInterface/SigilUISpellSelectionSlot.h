

#pragma once

#include "CoreMinimal.h"
#include "SigilUISpellSlot.h"
#include "SigilUISpellSelectionSlot.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUISpellSelectionSlot : public USigilUISpellSlot
{
	GENERATED_BODY()
	
public:

protected:

	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SlotHotkey_Text;

	int SlotHotkey;

public:

	/// <summary>
	/// Initialises this widget's properties
	/// </summary>
	/// <param name="InSpellInfo">The spell that this slot will represent</param>
	/// <param name="inSlotHotkey">The number assigned to this slot</param>
	virtual void SetInitialVariables(UDA_SpellInfo* InSpellInfo, int inSlotHotkey);

};
