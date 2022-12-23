

#pragma once

#include "CoreMinimal.h"
#include "SigilUISlot.h"
#include "SigilSpellTooltipWidget.h"
#include "SigilUISpellSlot.generated.h"

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

	virtual void SetInitialVariables(UDA_SpellInfo* InSpellInfo);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Reference")
		UDA_SpellInfo* SlotSpellInfo;

};
