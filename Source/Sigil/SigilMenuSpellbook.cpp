


#include "SigilMenuSpellbook.h"

void USigilMenuSpellbook::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetWidgetMinimumSize();

	WidgetName = UKismetTextLibrary::Conv_StringToText("Spellbook");
}

void USigilMenuSpellbook::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshSpellbookSlots();

	//Bind the buttons to their functions
	Button_AddToSpellbar->OnClicked.AddDynamic(this, &USigilMenuSpellbook::AddSpellToSpellbar);
	Button_CopySpell->OnClicked.AddDynamic(this, &USigilMenuSpellbook::CopySelectedSpell);
	Button_DeleteSpell->OnClicked.AddDynamic(this, &USigilMenuSpellbook::DeleteSelectedSpell);
	Button_NewSpell->OnClicked.AddDynamic(this, &USigilMenuSpellbook::CreateNewSpell);
	Button_RemoveFromSpellbar->OnClicked.AddDynamic(this, &USigilMenuSpellbook::RemoveSpellFromSpellbar);
	Button_SaveChanges->OnClicked.AddDynamic(this, &USigilMenuSpellbook::SaveChangesToSpell);

	//Bind button animations
	Button_AddToSpellbar->OnPressed.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_AddToSpellbar);
	Button_CopySpell->OnPressed.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_CopySpell);
	Button_DeleteSpell->OnPressed.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_DeleteSpell);
	Button_NewSpell->OnPressed.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_NewSpell);
	Button_RemoveFromSpellbar->OnPressed.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_RemoveFromSpellbar);
	Button_SaveChanges->OnPressed.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_SaveChanges);
	
	Button_AddToSpellbar->OnReleased.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_AddToSpellbar_Reverse);
	Button_CopySpell->OnReleased.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_CopySpell_Reverse);
	Button_DeleteSpell->OnReleased.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_DeleteSpell_Reverse);
	Button_NewSpell->OnReleased.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_NewSpell_Reverse);
	Button_RemoveFromSpellbar->OnReleased.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_RemoveFromSpellbar_Reverse);
	Button_SaveChanges->OnReleased.AddDynamic(this, &USigilMenuSpellbook::PlayButtonAnimation_SaveChanges_Reverse);


}

float USigilMenuSpellbook::ConvertFloatToPercentage(float InValue)
{
	//Converts a float value between 0 and 2 into a percentage value used by this widget's sliders. E.g. 0.2 -> -80%, 1.5 -> +50%
	if (InValue >= 1)
	{
		return (InValue - 1) * 100;
	}
	else
	{
		return ((1 - InValue) * 100) * -1;
	}
}

float USigilMenuSpellbook::ConvertPercentageToFloat(float InValue)
{
	//Converts a float value between -100 and 100 into the float value used by DA_SpellInfo's cost multiplier variables. E.g. -80 -> 0.2, 50 -> 1.5
	return (InValue / 100) + 1;
}

void USigilMenuSpellbook::Get_Slider_MPCostPercent_ToolTipText()
{
	Slider_MPCostPercent->SetToolTipText(CreateSliderTooltip(Slider_MPCostPercent));
}

void USigilMenuSpellbook::Get_Slider_DamagePercent_ToolTipText()
{
	Slider_DamagePercent->SetToolTipText(CreateSliderTooltip(Slider_DamagePercent));
}

void USigilMenuSpellbook::Get_Slider_SpeedPercent_ToolTipText()
{
	Slider_SpeedPercent->SetToolTipText(CreateSliderTooltip(Slider_SpeedPercent));
}

FText USigilMenuSpellbook::CreateSliderTooltip(USlider* InSlider)
{
	//Round the value of the InSlider and check if the result is a positive number
	if (UKismetMathLibrary::Round(InSlider->GetValue()) > 0)
	{
		//If true, convert the value to a string, prepend '+' to the value and append '%'. Convert the string to text and pass it into the return node.
		FString OutputString;

		OutputString.Append("+");
		OutputString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(InSlider->GetValue())));
		OutputString.Append("%");

		return UKismetTextLibrary::Conv_StringToText(OutputString);
	}
	else
	{
		//If false, convert the value to a string and append '%'. Convert the string to text and pass it into the return node.
		FString OutputString;

		OutputString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(InSlider->GetValue())));
		OutputString.Append("%");

		return UKismetTextLibrary::Conv_StringToText(OutputString);
	}
}

void USigilMenuSpellbook::CreateSpellbookTooltipWidget()
{
	if (SelectedSpell)
	{
		if (ScaleBox_Tooltip)
		{
			TooltipRef = CreateWidget<USigilSpellTooltipWidget>(GetParent(), SpellTooltipWidgetBP);
			TooltipRef->SetInitialVariables(SelectedSpell, true);

			ScaleBox_Tooltip->AddChild(TooltipRef);

			UWidgetLayoutLibrary::SlotAsScaleBoxSlot(TooltipRef)->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			UWidgetLayoutLibrary::SlotAsScaleBoxSlot(TooltipRef)->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
	}
}

void USigilMenuSpellbook::RefreshSpellbookSlots()
{
	ClearAllWrapBoxSlots();
	PopulateCoreSlots();
	PopulatePlayerSlots();
	PopulateComboBoxes();
	SetSelectedSlot();
}

void USigilMenuSpellbook::SetSelectedSlot()
{
	//If SelectedSpell is valid, search the Core Slotand Player Slot wrap boxes for the SelectedSpell.If it is found, set its SpellbookSlot as the new selected slot
	if (SelectedSlot)
	{
		if (!SearchWrapBoxForSelectedSpell(WrapBox_SpellbookCoreSlots))
		{
			//If SelectedSpell could not be found, set the first child of the Core Slot wrap box as the new selected slot
			if (!SearchWrapBoxForSelectedSpell(WrapBox_SpellbookPlayerSlots))
			{
				SetNewSelectedSlot(Cast<USigilUISpellbookSlot>(WrapBox_SpellbookCoreSlots->GetChildAt(0)));
			}
		}
	}
	else
	{
		//If SelectedSpell is not valid, set the first child of the Core Slot wrap box as the new selected slot
		SetNewSelectedSlot(Cast<USigilUISpellbookSlot>(WrapBox_SpellbookCoreSlots->GetChildAt(0)));
	}
}

void USigilMenuSpellbook::SetNewSelectedSlot(USigilUISpellbookSlot* NewSlot)
{
	//Clear any children inside the Tooltip scale box
	ScaleBox_Tooltip->ClearChildren();

	//Unselect the currently selected slot and set IsSelected to true for NewSlot, then set it as the new SelectedSlot.
	if (SelectedSlot)
	{
		SelectedSlot->SetIsSelected(false);
	}

	if (NewSlot)
	{
		NewSlot->SetIsSelected(true);
		SelectedSlot = NewSlot;
	}

	/*Get SlotSpellInfo from SelectedSlotand set is as the SelectedSpell. Call the ShowSpellProperties function to update 
	the information displayed in the spell properties vertical box*/
	if (SelectedSlot)
	{
		if (SelectedSlot->SlotSpellInfo)
		{
			SelectedSpell = SelectedSlot->SlotSpellInfo;

			ShowSpellProperties();
		}
	}

	CreateSpellbookTooltipWidget();
}

void USigilMenuSpellbook::PopulateCoreSlots()
{
	//Get all assets of class DA_SpellInfo
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;

	if (AssetRegistryModule.Get().GetAssetsByClass(UDA_SpellInfo::StaticClass()->GetFName(), AssetData))
	{
		int WrapBoxIndex = 0;

		//For each asset, cast it to DA_SpellInfo, create a SpellbookSlot widget, and add it as a child to the Core Slots wrap box
		for (FAssetData ArrayElement : AssetData)
		{
			FString SlotName = "CoreSpellSlot_";
			SlotName.Append(UKismetStringLibrary::Conv_IntToString(WrapBoxIndex));
			SlotName.Append("_");
			SlotName.Append(UKismetStringLibrary::Conv_NameToString(Cast<UDA_SpellInfo>(ArrayElement.GetAsset())->Name));

			if (USigilUISpellbookSlot* SpellbookSlot = CreateWidget<USigilUISpellbookSlot>(this, SpellbookSlotWidgetBP, UKismetStringLibrary::Conv_StringToName(SlotName)))
			{
				SpellbookSlot->SetInitialVariables(Cast<UDA_SpellInfo>(ArrayElement.GetAsset()), this);

				WrapBox_SpellbookCoreSlots->AddChildToWrapBox(SpellbookSlot);

				WrapBoxIndex++;
			}
		}
	}
}

void USigilMenuSpellbook::PopulatePlayerSlots()
{
	//Get the owning player's controlled pawn and cast it to SigilCharacter. Get the PlayerSpells array from the Spellbook component
	if (USpellbookComponent* SpellbookComponent = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn())->SpellcastingComponent->GetSpellbookComponent())
	{
		int WrapBoxIndex = 0;

		//For each item in the array, create a SpellbookSlot widget, and add it as a child to the Player Slots wrap box
		for (UDA_SpellInfo* SpellInfo : SpellbookComponent->PlayerSpells)
		{
			FString SlotName = "PlayerSpellSlot_";
			SlotName.Append(UKismetStringLibrary::Conv_IntToString(WrapBoxIndex));
			SlotName.Append("_");
			SlotName.Append(UKismetStringLibrary::Conv_NameToString(SpellInfo->Name));

			if (USigilUISpellbookSlot* SpellbookSlot = CreateWidget<USigilUISpellbookSlot>(this, SpellbookSlotWidgetBP, UKismetStringLibrary::Conv_StringToName(SlotName)))
			{
				SpellbookSlot->SetInitialVariables(SpellInfo, this);

				WrapBox_SpellbookPlayerSlots->AddChildToWrapBox(SpellbookSlot);

				WrapBoxIndex++;
			}
		}
	}
}

void USigilMenuSpellbook::Get_EditableTextBox_SpellName_HintText()
{
	if (SelectedSpell)
	{
		EditableTextBox_SpellName->SetText(UKismetTextLibrary::Conv_NameToText(SelectedSpell->Name));
	}
}

void USigilMenuSpellbook::Get_EditableTextBox_Potency_HintText()
{
	EditableTextBox_Potency->SetText(UKismetTextLibrary::Conv_StringToText("Numerical values only..."));
}

void USigilMenuSpellbook::PopulateComboBoxes()
{
	ClearComboBoxes();

	//Add every value from ESpellForm as an option to the Spell Form combo box
	for (ESpellForm SpellForm : TEnumRange<ESpellForm>())
	{
		ComboBoxString_PropertySpellForm->AddOption(UEnum::GetDisplayValueAsText(SpellForm).ToString());
		SpellFormTypes.AddUnique(SpellForm);
	}

	//Add every value from ESpellTarget as an option to the Target combo box
	for (ESpellTarget SpellTarget : TEnumRange<ESpellTarget>())
	{
		ComboBoxString_PropertyTarget->AddOption(UEnum::GetDisplayValueAsText(SpellTarget).ToString());
		SpellTargetTypes.AddUnique(SpellTarget);
	}
	
	//Add every value from EMagicElement as an option to the Element combo box
	for (EMagicElementType MagicElement : TEnumRange<EMagicElementType>())
	{
		ComboBoxString_PropertyElement->AddOption(UEnum::GetDisplayValueAsText(MagicElement).ToString());
		MagicElementTypes.AddUnique(MagicElement);
	}
}

void USigilMenuSpellbook::ClearComboBoxes()
{
	//Clear the options from all combo boxes
	ComboBoxString_PropertySpellForm->ClearOptions();
	ComboBoxString_PropertyTarget->ClearOptions();
	ComboBoxString_PropertyElement->ClearOptions();
}

void USigilMenuSpellbook::ConvertSliderValues()
{
	//Pass the value of the MPCostPercent slider into ConvertPercentageToFloat. Set NewSpellMPCostMultiplier to the function's output
	NewSpell_MPCostMultiplier = ConvertPercentageToFloat(Slider_MPCostPercent->GetValue());

	//Pass the value of the DamagePercent slider into ConvertPercentageToFloat. Set NewSpellDamageMultiplier to the function's output
	NewSpell_DamageMultiplier = ConvertPercentageToFloat(Slider_DamagePercent->GetValue());

	//Pass the value of the SpeedPercent slider into ConvertPercentageToFloat. Set NewSpellSpeedMultiplier to the function's output
	NewSpell_SpeedMultiplier = ConvertPercentageToFloat(Slider_SpeedPercent->GetValue());
}

void USigilMenuSpellbook::ClearAllWrapBoxSlots()
{
	//Remove any children from the wrap boxes
	WrapBox_SpellbookCoreSlots->ClearChildren();
	WrapBox_SpellbookPlayerSlots->ClearChildren();
}

bool USigilMenuSpellbook::SearchWrapBoxForSelectedSpell(UWrapBox* InWrapBox)
{
	//Check that InWrapBox has children before continuing
	if (InWrapBox->HasAnyChildren())
	{
		//Get each child of InWrapBox that is a SpellbookSlot widget
		for (size_t i = 0; i < InWrapBox->GetChildrenCount(); i++)
		{
			if (USigilUISpellbookSlot* ChildSlot = Cast<USigilUISpellbookSlot>(InWrapBox->GetChildAt(i)))
			{
				//Check if its SlotSpellInfo is the same as SelectedSpell
				if (ChildSlot->SlotSpellInfo == SelectedSpell)
				{
					//Call SetNewSelectedSlot with ChildSlot as NewSlot, return true
					SetNewSelectedSlot(ChildSlot);
					return true;
				}
			}
		}
	}

	//If not matching spell is found, return false
	return false;
}

void USigilMenuSpellbook::SetWidgetMinimumSize()
{
	//Set the Widget's minimum height and width, these two variables will be used by the WindowFrame widget
	WidgetMinimumWidth = Spellbook->MinDesiredWidth;
	WidgetMinimumHeight = Spellbook->MinDesiredHeight;
}

void USigilMenuSpellbook::ShowSpellProperties()
{
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//Set the text of the SpellName text box to the Name of SelectedSpell
		if (EditableTextBox_SpellName)
		{
			EditableTextBox_SpellName->SetText(UKismetTextLibrary::Conv_NameToText(SelectedSpell->Name));
		}

		//Set the selected option of the SpellForm combo box to the Form of SelectedSpell
		if (ComboBoxString_PropertySpellForm)
		{
			ComboBoxString_PropertySpellForm->SetSelectedOption(UEnum::GetDisplayValueAsText(SelectedSpell->Form).ToString());
		}

		//Get MPCostMultiplier from SelectedSpell and pass it into the function ConvertFloatToPercentage. Set the value of the MPCostPercent slider to the function's output.
		if (Slider_MPCostPercent)
		{
			Slider_MPCostPercent->SetValue(ConvertFloatToPercentage(SelectedSpell->MPCostMultiplier));
		}

		//Get DamageMultiplier from SelectedSpell and pass it into the function ConvertFloatToPercentage. Set the value of the DamagePercent slider to the function's output.
		if (Slider_DamagePercent)
		{
			Slider_DamagePercent->SetValue(ConvertFloatToPercentage(SelectedSpell->DamageMultiplier));
		}

		//Get SpeedMultiplier from SelectedSpell and pass it into the function ConvertFloatToPercentage. Set the value of the SpeedPercent slider to the function's output.
		if (Slider_SpeedPercent)
		{
			Slider_SpeedPercent->SetValue(ConvertFloatToPercentage(SelectedSpell->SpeedMultiplier));
		}

		//Set IsChecked on the Homing check box to the value of IsHoming from SelectedSpell
		if (CheckBox_Homing)
		{
			CheckBox_Homing->SetIsChecked(SelectedSpell->bIsHoming);
		}

		//Set the selected option of the Target combo box to the Target of SelectedSpell
		if (ComboBoxString_PropertyTarget)
		{
			ComboBoxString_PropertyTarget->SetSelectedOption(UEnum::GetDisplayValueAsText(SelectedSpell->Target).ToString());
		}

		//Set the selected option of the Element combo box to the ElementType of SelectedSpell's BaseSpellDamage first element
		if (ComboBoxString_PropertyElement)
		{
			ComboBoxString_PropertyElement->SetSelectedOption(UEnum::GetDisplayValueAsText(SelectedSpell->SpellDamage[0].ElementType).ToString());
		}

		//Set the text of the Potency text box to DamageAmount from the same element
		if (EditableTextBox_Potency)
		{
			EditableTextBox_Potency->SetText(UKismetTextLibrary::Conv_FloatToText(SelectedSpell->SpellDamage[0].DamageAmount, ERoundingMode::HalfToEven));
		}

		//If CanEdit from SelectedSpell is true, change the colour of the SaveChanges and DeleteSpell buttons to white. If false, make them dark grey.
		if (Button_SaveChanges)
		{
			if (Button_DeleteSpell)
			{
				if (SelectedSpell->bCanEdit)
				{
					Button_SaveChanges->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
					Button_DeleteSpell->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
				}
				else
				{
					Button_SaveChanges->SetColorAndOpacity(FLinearColor(0.1, 0.1, 0.1, 1));
					Button_DeleteSpell->SetColorAndOpacity(FLinearColor(0.1, 0.1, 0.1, 1));
				}
			}
		}

		//Call SetNewSpellProperties
		SetNewSpellProperties();
	}
}

void USigilMenuSpellbook::SetNewSpellProperties()
{
	//Set NewSpellName to the text of the SpellName text box
	if (EditableTextBox_SpellName)
	{
		NewSpell_Name = UKismetStringLibrary::Conv_StringToName(EditableTextBox_SpellName->GetText().ToString());
	}

	//Set NewSpellForm to the selected option of the SpellForm combo box
	if (ComboBoxString_PropertySpellForm)
	{
		int SelectedIndex = UKismetMathLibrary::Clamp(ComboBoxString_PropertySpellForm->GetSelectedIndex(), 0, SpellFormTypes.Num() - 1);
		NewSpell_Form = SpellFormTypes[SelectedIndex];
	}

	//Call ConvertSliderValues
	ConvertSliderValues();

	//Set NewSpellIsHoming to the value of IsChecked from the Homing check box
	if (CheckBox_Homing)
	{
		bNewSpell_IsHoming = CheckBox_Homing->IsChecked();
	}

	//Set NewSpellSpellTarget to the selected option of the Target combo box
	if (ComboBoxString_PropertyTarget)
	{
		int SelectedIndex = UKismetMathLibrary::Clamp(ComboBoxString_PropertyTarget->GetSelectedIndex(), 0, SpellTargetTypes.Num() - 1);
		NewSpell_Target = SpellTargetTypes[SelectedIndex];
	}

	//Set NewSpellSpellElement to the selected option of the Element combo box
	if (ComboBoxString_PropertyElement)
	{
		int SelectedIndex = UKismetMathLibrary::Clamp(ComboBoxString_PropertyElement->GetSelectedIndex(), 0, MagicElementTypes.Num() - 1);
		NewSpell_MagicElement = MagicElementTypes[SelectedIndex];
	}

	//Set NewSpellPotency to the text of the Potency text box if the value is numeric
	if (EditableTextBox_Potency)
	{
		if (UKismetStringLibrary::IsNumeric(EditableTextBox_Potency->GetText().ToString()))
		{
			NewSpell_Potency = UKismetStringLibrary::Conv_StringToFloat(EditableTextBox_Potency->GetText().ToString());
		}
	}
}

void USigilMenuSpellbook::AddSpellToSpellbar()
{
	if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		if (SelectedSpell)
		{
			PC->AddSpellToSpellbar(SelectedSpell);
		}
	}
}

void USigilMenuSpellbook::CopySelectedSpell()
{
	if (SelectedSpell)
	{
		//Create a new DASpellInfo object and give it the same properties as SelectedSpell. Rename the spell and set CanEdit to true.
		UDA_SpellInfo* CopiedSpell = NewObject<UDA_SpellInfo>(this);

		CopiedSpell->SetSpellProperties(SelectedSpell->GetSpellProperties());
		
		FString NewName = "Copy of ";
		NewName.Append(SelectedSpell->Name.ToString());

		CopiedSpell->Name = UKismetStringLibrary::Conv_StringToName(NewName);
		CopiedSpell->bCanEdit = true;

		//Add the Copied spell to the player's spellbook component
		if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
		{
			SC->AddSpellToSpellbook(CopiedSpell);
		}

		RefreshSpellbookSlots();
	}
}

void USigilMenuSpellbook::CreateNewSpell()
{
	//Create a new DASpellInfo object and set its properties
	UDA_SpellInfo* CreatedSpell = NewObject<UDA_SpellInfo>(this);
	CreatedSpell->bCanEdit = true;

	/*FSpellProperties NewSpellProperties;
	NewSpellProperties.Name = FName("New Spell");
	NewSpellProperties.Form = ESpellForm::Dart;
	NewSpellProperties.BaseMPCost = 10.0f;
	NewSpellProperties.BaseSpeed = 1000.0f;
	NewSpellProperties.BaseAcceleration = 250.0f;

	FSpellElements NewElement;
	NewElement.ElementType = EMagicElementType::Aether;
	NewElement.DamageAmount = 10.0f;
	NewSpellProperties.BaseSpellDamage.Add(NewElement);

	NewSpellProperties.MPCostMultiplier = 1.0f;
	NewSpellProperties.DamageMultiplier = 1.0f;
	NewSpellProperties.SpeedMultiplier = 1.0f;
	NewSpellProperties.bIsHoming = false;
	NewSpellProperties.Target = ESpellTarget::NotApplicable;*/

	CreatedSpell->SetSpellProperties(NewSpellDefaultProperties);

	//Add the new spell to the player's Spellbook and refresh the widget.
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
	{
		SC->AddSpellToSpellbook(CreatedSpell);
	}

	RefreshSpellbookSlots();
}

void USigilMenuSpellbook::DeleteSelectedSpell()
{
	//Check that the spell can be edited before proceeding
	if (SelectedSpell)
	{
		if (SelectedSpell->bCanEdit)
		{
			if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
			{
				//Remove the spell from the player's spellbook component
				if (SC->RemoveSpellFromSpellbook(SelectedSpell))
				{
					//Remove the spell from the player's Spell Bar
					if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(SC->GetOwner()))
					{
						PC->RemoveSpellFromSpellbar(SelectedSpell);
					}
				}
			}
		}

		RefreshSpellbookSlots();
	}
}

void USigilMenuSpellbook::RemoveSpellFromSpellbar()
{
	if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		if (SelectedSpell)
		{
			PC->RemoveSpellFromSpellbar(SelectedSpell);
		}
	}
}

void USigilMenuSpellbook::SaveChangesToSpell()
{
	SetNewSpellProperties();

	//Set the properties of SelectedSpells by calling SetSpellProperties from DASpellInfo
	if (SelectedSpell)
	{
		if (SelectedSpell->bCanEdit)
		{
			SelectedSpell->Name = NewSpell_Name;

			FSpellProperties NewSpellProperties;
			NewSpellProperties.Name = NewSpell_Name;
			NewSpellProperties.Form = NewSpell_Form;
			NewSpellProperties.BaseMPCost = SelectedSpell->BaseMPCost;
			NewSpellProperties.BaseSpeed = SelectedSpell->BaseSpeed;
			NewSpellProperties.BaseAcceleration = SelectedSpell->BaseAcceleration;

			NewSpellProperties.Thumbnail = SelectedSpell->Thumbnail;
			NewSpellProperties.Mesh = SelectedSpell->Mesh;
			NewSpellProperties.CastSFX = SelectedSpell->CastSFX;
			NewSpellProperties.HitSFX = SelectedSpell->HitSFX;

			FSpellElements NewElement;
			NewElement.ElementType = NewSpell_MagicElement;
			NewElement.DamageAmount = NewSpell_Potency;
			NewSpellProperties.BaseSpellDamage.Add(NewElement);

			NewSpellProperties.MPCostMultiplier = NewSpell_MPCostMultiplier;
			NewSpellProperties.DamageMultiplier = NewSpell_DamageMultiplier;
			NewSpellProperties.SpeedMultiplier = NewSpell_SpeedMultiplier;
			NewSpellProperties.bIsHoming = bNewSpell_IsHoming;
			NewSpellProperties.Target = NewSpell_Target;

			SelectedSpell->SetSpellProperties(NewSpellProperties);

			RefreshSpellbookSlots();
		}
	}
}

void USigilMenuSpellbook::PlayButtonAnimation(UWidgetAnimation* InAnimation, EUMGSequencePlayMode::Type PlayMode)
{
	if (InAnimation)
	{
		PlayAnimation(InAnimation, 0, 1, PlayMode, 1.0f, false);
	}
}

void USigilMenuSpellbook::PlayButtonAnimation_AddToSpellbar()
{
	PlayButtonAnimation(Anim_ButtonPress_AddToSpellbar, EUMGSequencePlayMode::Forward);
}

void USigilMenuSpellbook::PlayButtonAnimation_AddToSpellbar_Reverse()
{
	PlayButtonAnimation(Anim_ButtonPress_AddToSpellbar, EUMGSequencePlayMode::Reverse);
}

void USigilMenuSpellbook::PlayButtonAnimation_CopySpell()
{
	PlayButtonAnimation(Anim_ButtonPress_CopySpell, EUMGSequencePlayMode::Forward);
}

void USigilMenuSpellbook::PlayButtonAnimation_CopySpell_Reverse()
{
	PlayButtonAnimation(Anim_ButtonPress_CopySpell, EUMGSequencePlayMode::Reverse);
}

void USigilMenuSpellbook::PlayButtonAnimation_DeleteSpell()
{
	PlayButtonAnimation(Anim_ButtonPress_DeleteSpell, EUMGSequencePlayMode::Forward);
}

void USigilMenuSpellbook::PlayButtonAnimation_DeleteSpell_Reverse()
{
	PlayButtonAnimation(Anim_ButtonPress_DeleteSpell, EUMGSequencePlayMode::Reverse);
}

void USigilMenuSpellbook::PlayButtonAnimation_NewSpell()
{
	PlayButtonAnimation(Anim_ButtonPress_NewSpell, EUMGSequencePlayMode::Forward);
}

void USigilMenuSpellbook::PlayButtonAnimation_NewSpell_Reverse()
{
	PlayButtonAnimation(Anim_ButtonPress_NewSpell, EUMGSequencePlayMode::Reverse);
}

void USigilMenuSpellbook::PlayButtonAnimation_RemoveFromSpellbar()
{
	PlayButtonAnimation(Anim_ButtonPress_RemoveFromSpellbar, EUMGSequencePlayMode::Forward);
}

void USigilMenuSpellbook::PlayButtonAnimation_RemoveFromSpellbar_Reverse()
{
	PlayButtonAnimation(Anim_ButtonPress_RemoveFromSpellbar, EUMGSequencePlayMode::Reverse);
}

void USigilMenuSpellbook::PlayButtonAnimation_SaveChanges()
{
	PlayButtonAnimation(Anim_ButtonPress_SaveChanges, EUMGSequencePlayMode::Forward);
}

void USigilMenuSpellbook::PlayButtonAnimation_SaveChanges_Reverse()
{
	PlayButtonAnimation(Anim_ButtonPress_SaveChanges, EUMGSequencePlayMode::Reverse);
}
