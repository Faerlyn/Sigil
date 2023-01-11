

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SigilTextTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilTextTooltipWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_TooltipText;

	FText WidgetText;
	FText* TextRef;

public:

	//Returns the text value of the tooltip
	UFUNCTION()
	FText GetWidgetText();

	//Set the text in the tooltip, will be ovewritten by TextRef if it is valid.
	void SetWidgetText(FText InText);

	//Set a reference to an FText variable if you want the tooltip to update the text value on tick. This will overwrite the SetWidgetText function.
	void SetWidgetTextRef(FText* InTextRef);

};
