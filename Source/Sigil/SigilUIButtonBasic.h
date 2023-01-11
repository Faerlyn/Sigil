

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "SigilUIButtonBasic.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUIButtonBasic : public UUserWidget
{
	GENERATED_BODY()

public:


protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient, Category = "Sigil Button | Animations")
		UWidgetAnimation* Anim_ButtonPressed = nullptr;

	UPROPERTY(meta = (BindWidget))
		UButton* SigilUIButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SigilUIButton_Label;

	UPROPERTY(EditAnywhere, Category = "Sigil Button | Text")
		FText ButtonLabelText = FText(UKismetTextLibrary::Conv_StringToText("Button Label"));

	UFUNCTION()
		void SigilUIButton_OnPressed();
	
	UFUNCTION()
		void SigilUIButton_OnReleased();

public:

	UButton* GetButton() { return SigilUIButton; };

	FText GetButtonLabelText() { return ButtonLabelText; };

	void SetButtonLabelText(FText InText);

};
