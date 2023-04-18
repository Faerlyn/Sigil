


#include "SigilUIButtonBasic.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void USigilUIButtonBasic::NativePreConstruct()
{
	Super::NativePreConstruct();

	//Validate SigilUIButton_Label
	if (SigilUIButton_Label)
	{
		//Set the text of SigilUIButton_Label so that it can be previewed in the blueprint editor
		SigilUIButton_Label->SetText(ButtonLabelText);
	}
}

void USigilUIButtonBasic::NativeConstruct()
{
	Super::NativeConstruct();
	
	//Bind button delegates
	SigilUIButton->OnPressed.AddUniqueDynamic(this, &USigilUIButtonBasic::SigilUIButton_OnPressed);
	SigilUIButton->OnReleased.AddUniqueDynamic(this, &USigilUIButtonBasic::SigilUIButton_OnReleased);

	SigilUIButton->SynchronizeProperties();

}

void USigilUIButtonBasic::SigilUIButton_OnPressed()
{
	//Validate Anim_ButtonPressed
	if (Anim_ButtonPressed)
	{
		//Play the button pressed animation
		PlayAnimation(Anim_ButtonPressed, 0, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
	}
}

void USigilUIButtonBasic::SigilUIButton_OnReleased()
{
	//Validate Anim_ButtonPressed
	if (Anim_ButtonPressed)
	{
		//Play the button pressed animation in reverse
		PlayAnimation(Anim_ButtonPressed, 0, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
	}
}

void USigilUIButtonBasic::SetButtonLabelText(FText InText)
{
	//Overwrite ButtonLabelText with InText
	ButtonLabelText = InText;

	//Validate SigilUIButton_Label
	if (SigilUIButton_Label)
	{
		//Update the text block to use the new text value
		SigilUIButton_Label->SetText(ButtonLabelText);
	}
}
