

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

protected:

	// Called when a mouse button is pressed within this widget
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//Stores a reference to the widget that is the parent of this widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Reference")
		UWidget* OwningWidget;

public:

	/// <summary>
	/// Initialises this widget's properties
	/// </summary>
	/// <param name="InSpellInfo">The spell that this slot will represent</param>
	/// <param name="ParentWidget">This widget's parent widget</param>
	virtual void SetInitialVariables(UDA_SpellInfo* InSpellInfo, UWidget* ParentWidget);

};
