

#pragma once

#include "CoreMinimal.h"
#include "SigilUISpellSlot.h"
#include "SigilUISpellbookSlot.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUISpellbookSlot : public USigilUISpellSlot
{
	GENERATED_BODY()
	
public:

	virtual void SetInitialVariables(UDA_SpellInfo* InSpellInfo, UWidget* ParentWidget);

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Reference")
		UWidget* OwningWidget;

};
