

#pragma once

#include "CoreMinimal.h"
#include "SigilUISlot.h"
#include "SigilUISpellSlot.generated.h"

class USigilSpellTooltipWidget;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUISpellSlot : public USigilUISlot
{
	GENERATED_BODY()
	
public:


protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void SetSlotImage() override;
	virtual UWidget* GetToolTipWidget() override;

	UPROPERTY(EditAnywhere, Category = "Reference")
		TSubclassOf<USigilSpellTooltipWidget> SpellTooltipWidgetBP;

public:

	/// <summary>
	/// Initialises this widget's properties
	/// </summary>
	/// <param name="InSpellInfo">The spell that this slot will represent</param>
	virtual void SetInitialVariables(UDA_SpellInfo* InSpellInfo);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Reference")
		UDA_SpellInfo* SlotSpellInfo;

};
