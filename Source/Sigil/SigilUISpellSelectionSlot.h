

#pragma once

#include "CoreMinimal.h"
#include "SigilUISpellSlot.h"
#include "Components/TextBlock.h"
#include "SigilPlayerController.h"
#include "SigilCharacter.h"
#include "SigilUISpellSelectionSlot.generated.h"

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

	int SlotHotkey;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SlotHotkey_Text;

public:

	virtual void SetInitialVariables(UDA_SpellInfo* InSpellInfo, int inSlotHotkey);

};
