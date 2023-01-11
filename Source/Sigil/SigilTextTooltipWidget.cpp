


#include "SigilTextTooltipWidget.h"

void USigilTextTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Validate TextBlock_TooltipText
	if (TextBlock_TooltipText)
	{
		//If TextRef is not nullptr
		if (TextRef)
		{
			//Bind textblock delegates
			TextBlock_TooltipText->TextDelegate.BindDynamic(this, &USigilTextTooltipWidget::GetWidgetText);
			TextBlock_TooltipText->SynchronizeProperties();
		}
	}
}

FText USigilTextTooltipWidget::GetWidgetText()
{
	//Validate TextRef
	if (TextRef)
	{
		//Return the text of TextBlock_TooltipText
		return *TextRef;
	}

	//If validation fails, return WidgetText
	return WidgetText;
}

void USigilTextTooltipWidget::SetWidgetText(FText InText)
{
	//Validate TextBlock_TooltipText
	if (TextBlock_TooltipText)
	{
		//Set the text of TextBlock_TooltipText to InText
		TextBlock_TooltipText->SetText(InText);
	}
}

void USigilTextTooltipWidget::SetWidgetTextRef(FText* InTextRef)
{
	//Validate InTextRef
	if (InTextRef)
	{
		//Set the new Text Reference
		TextRef = InTextRef;
	}
}
