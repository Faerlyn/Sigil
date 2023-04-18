

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilUIButtonBasic.generated.h"

class UButton;
class UTextBlock;

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

	//This text is displayed on the button as its label
	UPROPERTY(EditAnywhere, Category = "Sigil Button | Text")
		FText ButtonLabelText = FText::FromString("Button Label");
		//FText ButtonLabelText = FText(UKismetTextLibrary::Conv_StringToText("Button Label"));

	//Called when the button is pressed
	UFUNCTION()
		void SigilUIButton_OnPressed();
	
	//Called when the button is released
	UFUNCTION()
		void SigilUIButton_OnReleased();

public:

	//Getter for SigilUIButton
	UButton* GetButton() { return SigilUIButton; };

	//Getter for ButtonLabelText
	FText GetButtonLabelText() { return ButtonLabelText; };

	// Setter for ButtonLabeText
	void SetButtonLabelText(FText InText);

};
