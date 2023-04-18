


#include "SigilUIPercentageSlider.h"

#include "Components/Slider.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

#include "SigilTextTooltipWidget.h"

void USigilUIPercentageSlider::NativeConstruct()
{
	Super::NativeConstruct();

	//Validate PercentageSlider
	if (PercentageSlider)
	{
		//Bind delegates
		PercentageSlider->ToolTipWidgetDelegate.BindDynamic(this, &USigilUIPercentageSlider::GetTooltipWidget);
		PercentageSlider->SynchronizeProperties();
	}

}

void USigilUIPercentageSlider::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SliderText = CreateSliderTooltipText();
}

UWidget* USigilUIPercentageSlider::GetTooltipWidget()
{
	//Validate TextTooltipWidgetBP
	if (TextTooltipWidgetBP)
	{
		//Create a new USigilTextTooltipWidget widget
		USigilTextTooltipWidget* SliderTooltipWidget = CreateWidget<USigilTextTooltipWidget>(this, TextTooltipWidgetBP);

		//Set the tooltip's text to SliderText
		SliderTooltipWidget->SetWidgetTextRef(&SliderText);

		//Return the widget
		return SliderTooltipWidget;
	}
	return nullptr;
}

FText USigilUIPercentageSlider::CreateSliderTooltipText()
{
	//Validate PercentageSlider
	if (PercentageSlider)
	{
		//Round the value of the Slider and check if the result is a positive number
		if (UKismetMathLibrary::Round(PercentageSlider->GetValue() > 0))
		{
			//If true, convert the value to a string, prepend '+' to the value and append '%'. Convert the string to text and pass it into the return node.
			//E.g. +50%
			FString OutputString;

			OutputString.Append("+");
			OutputString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(PercentageSlider->GetValue())));
			OutputString.Append("%");

			return UKismetTextLibrary::Conv_StringToText(OutputString);
		}
		else
		{
			//If false, convert the value to a string and append '%'. Convert the string to text and pass it into the return node.
			//E.g. 75%
			FString OutputString;

			OutputString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(PercentageSlider->GetValue())));
			OutputString.Append("%");

			return UKismetTextLibrary::Conv_StringToText(OutputString);
		}
	}

	//If validation fails, log an error
	UE_LOG(LogTemp, Warning, TEXT("PercentageSlider is not valid"));
	return FText();
}

float USigilUIPercentageSlider::GetSliderValue()
{
	return PercentageSlider->GetValue();
}

void USigilUIPercentageSlider::SetSliderValue(float InFloat)
{
	PercentageSlider->SetValue(InFloat);
}