

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "SigilTextTooltipWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "SigilUIPercentageSlider.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUIPercentageSlider : public UUserWidget
{
	GENERATED_BODY()
	
public:

	float GetSliderValue() { return PercentageSlider->GetValue(); }

	void SetSliderValue(float InFloat) { PercentageSlider->SetValue(InFloat); }

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY(meta = (BindWidget))
		USlider* PercentageSlider;

	UPROPERTY(EditAnywhere, Category = "Percentage Slider | Reference")
		TSubclassOf<UUserWidget> TextTooltipWidgetBP;

	FText SliderText;

	UFUNCTION()
	UWidget* GetTooltipWidget();

	FText CreateSliderTooltipText();
};
