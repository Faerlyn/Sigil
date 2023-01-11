


#include "SigilUIPercentageSlider.h"

void USigilUIPercentageSlider::NativeConstruct()
{
	Super::NativeConstruct();

	PercentageSlider->ToolTipWidgetDelegate.BindDynamic(this, &USigilUIPercentageSlider::GetTooltipWidget);
	PercentageSlider->SynchronizeProperties();
}

void USigilUIPercentageSlider::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SliderText = CreateSliderTooltipText();
}

UWidget* USigilUIPercentageSlider::GetTooltipWidget()
{
	if (TextTooltipWidgetBP)
	{
		USigilTextTooltipWidget* SliderTooltipWidget = CreateWidget<USigilTextTooltipWidget>(this, TextTooltipWidgetBP);
		SliderTooltipWidget->SetWidgetTextRef(&SliderText);

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
			FString OutputString;

			OutputString.Append("+");
			OutputString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(PercentageSlider->GetValue())));
			OutputString.Append("%");

			return UKismetTextLibrary::Conv_StringToText(OutputString);
		}
		else
		{
			//If false, convert the value to a string and append '%'. Convert the string to text and pass it into the return node.
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
