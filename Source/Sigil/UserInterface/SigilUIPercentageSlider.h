

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilUIPercentageSlider.generated.h"

class USlider;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUIPercentageSlider : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(meta = (BindWidget))
		USlider* PercentageSlider;

	UPROPERTY(EditAnywhere, Category = "Percentage Slider | Reference")
		TSubclassOf<UUserWidget> TextTooltipWidgetBP;

	FText SliderText;

	// Called when the ToolTipWidgetDelegate is executed
	UFUNCTION()
	UWidget* GetTooltipWidget();

	/// <summary>
	/// Converts the PercentageSlider's value to a percentage
	/// E.g. 0.2 -> "20%", 1.5 -> "+150%"
	/// </summary>
	/// <returns>Returns a text value</returns>
	FText CreateSliderTooltipText();

public:

	//Getter for PercentageSlider's value
	float GetSliderValue();


	//Setter for PercentageSlider's value
	void SetSliderValue(float InFloat);

};
