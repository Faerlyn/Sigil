


#include "SigilMenuSpellbook.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/ScaleBox.h"
#include "Components/ScaleBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/Slider.h"
#include "Components/WrapBox.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

#include "../Actor/Character/SigilCharacter.h"
#include "../Actor/Component/SpellbookComponent.h"
#include "../Actor/Component/SpellcastingComponent.h"
#include "../Controller/SigilPlayerController.h"
#include "../DataAsset/UDA_SpellInfo.h"
#include "SigilSpellTooltipWidget.h"
#include "SigilUIButtonBasic.h"
#include "SigilUIPercentageSlider.h"
#include "SigilUISpellbookSlot.h"


void USigilMenuSpellbook::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetWidgetMinimumSize();

	//Set WidgetName, which is used when this widget is added to the WindowFrame widget
	WidgetName = UKismetTextLibrary::Conv_StringToText("Spellbook");
}

void USigilMenuSpellbook::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshSpellbookSlots();

	//Bind the buttons to their functions
	Button_AddToSpellbar->GetButton()->OnClicked.AddUniqueDynamic(this, &USigilMenuSpellbook::AddSpellToSpellbar);
	Button_AddToSpellbar->SynchronizeProperties();

	Button_CopySpell->GetButton()->OnClicked.AddUniqueDynamic(this, &USigilMenuSpellbook::CopySelectedSpell);
	Button_CopySpell->SynchronizeProperties();

	Button_DeleteSpell->GetButton()->OnClicked.AddUniqueDynamic(this, &USigilMenuSpellbook::DeleteSelectedSpell);
	Button_DeleteSpell->SynchronizeProperties();

	Button_NewSpell->GetButton()->OnClicked.AddUniqueDynamic(this, &USigilMenuSpellbook::CreateNewSpell);
	Button_NewSpell->SynchronizeProperties();

	Button_RemoveFromSpellbar->GetButton()->OnClicked.AddUniqueDynamic(this, &USigilMenuSpellbook::RemoveSelectedSpellFromSpellbar);
	Button_RemoveFromSpellbar->SynchronizeProperties();

	Button_SaveChanges->GetButton()->OnClicked.AddUniqueDynamic(this, &USigilMenuSpellbook::SaveChangesToSpell);
	Button_SaveChanges->SynchronizeProperties();

	
	//Bind delegates for textbox hint text
	EditableTextBox_SpellName->HintTextDelegate.BindDynamic(this, &USigilMenuSpellbook::Get_EditableTextBox_SpellName_HintText);
	EditableTextBox_SpellName->SynchronizeProperties();

	EditableTextBox_Potency->HintTextDelegate.BindDynamic(this, &USigilMenuSpellbook::Get_EditableTextBox_Potency_HintText);
	EditableTextBox_Potency->SynchronizeProperties();
}

float USigilMenuSpellbook::ConvertFloatToPercentage(float InValue)
{
	return (InValue - 1) * 100;
}

float USigilMenuSpellbook::ConvertPercentageToFloat(float InValue)
{
	return (InValue / 100) + 1;
}

void USigilMenuSpellbook::CreateSpellbookTooltipWidget()
{
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//Validate ScaleBox_Tooltip
		if (ScaleBox_Tooltip)
		{
			//Remove any children from ScaleBox_Tooltip
			ScaleBox_Tooltip->ClearChildren();

			//Create a SigilSpellTooltip widget using the SpellTooltip blueprint reference defined in the Spellbook blueprint
			TooltipRef = CreateWidget<USigilSpellTooltipWidget>(GetParent(), SpellTooltipWidgetBP);

			//Call SetInitialVariables for the new widget
			TooltipRef->SetInitialVariables(SelectedSpell, true);

			//Make the widget a child of ScaleBox_Tooltip
			ScaleBox_Tooltip->AddChild(TooltipRef);

			//Slot TooltipRef as a ScaleBoxSlot and set its horizontal and vertical alignment to fill
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
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//If SelectedSpell could not be found in WrapBox_SpellbookCoreSlots
		if (!SearchWrapBoxForSelectedSpell(WrapBox_SpellbookCoreSlots))
		{
			//Search WrapBox_SpellbookPlayerSlots for SelectedSpell
			if (!SearchWrapBoxForSelectedSpell(WrapBox_SpellbookPlayerSlots))
			{
				//If neither search could find SelectedSpell, call SetNewSelectSlot for the first child of WrapBox_SpellbookCoreSlots
				SetNewSelectedSlot(Cast<USigilUISpellbookSlot>(WrapBox_SpellbookCoreSlots->GetChildAt(0)));
			}
		}
	}
	else
	{
		//If SelectedSpell is not valid, call SetNewSelectSlot for the first child of WrapBox_SpellbookCoreSlots
		SetNewSelectedSlot(Cast<USigilUISpellbookSlot>(WrapBox_SpellbookCoreSlots->GetChildAt(0)));
	}
}

void USigilMenuSpellbook::SetNewSelectedSlot(USigilUISpellbookSlot* NewSlot)
{
	//Validate SelectedSlot
	if (SelectedSlot)
	{
		//Set IsSelected to false
		SelectedSlot->SetIsSelected(false);
	}

	//Validate NewSlot
	if (NewSlot)
	{
		//Set IsSelected to true
		NewSlot->SetIsSelected(true);

		//Set NewSlot as the new SelectedSlot
		SelectedSlot = NewSlot;
	}

	//Validate SelectedSlot
	if (SelectedSlot)
	{
		//Validate SelectedSlot's SlotSpellInfo
		if (SelectedSlot->SlotSpellInfo)
		{
			//Set SlotSpellInfo as the new SelectedSpell
			SelectedSpell = SelectedSlot->SlotSpellInfo;

			//Call ShowSpellProperties to update the information displayed in the spell properties vertical box
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
		int ArrayIndex = 0;

		//For each asset
		for (FAssetData ArrayElement : AssetData)
		{
			//Create the name of the widget using the following format: CoreSpellSlot_[ArrayIndex]_[SpellInfo->Name] e.g. CoreSpellSlot_1_Fireball
			FString SlotName = "CoreSpellSlot_";
			SlotName.Append(UKismetStringLibrary::Conv_IntToString(ArrayIndex));
			SlotName.Append("_");
			SlotName.Append(UKismetStringLibrary::Conv_NameToString(Cast<UDA_SpellInfo>(ArrayElement.GetAsset())->Name));

			//Cast it to DA_SpellInfo and create a SpellbookSlot widget
			if (USigilUISpellbookSlot* SpellbookSlot = CreateWidget<USigilUISpellbookSlot>(this, SpellbookSlotWidgetBP, UKismetStringLibrary::Conv_StringToName(SlotName)))
			{
				//Call SetInitialVariables for the new widget
				SpellbookSlot->SetInitialVariables(Cast<UDA_SpellInfo>(ArrayElement.GetAsset()), this);

				//Make the new widget a child of the wrap box
				WrapBox_SpellbookCoreSlots->AddChildToWrapBox(SpellbookSlot);

				//Increment ArrayIndex
				ArrayIndex++;
			}
		}
	}
}

void USigilMenuSpellbook::PopulatePlayerSlots()
{
	//Get the owning player's controlled pawn and cast it to SigilCharacter. Get the pawn's Spellbook component
	if (USpellbookComponent* SpellbookComponent = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn())->GetSpellcastingComponent()->GetSpellbookComponent())
	{
		int ArrayIndex = 0;

		//For each item in the PlayerSpells array
		for (UDA_SpellInfo* SpellInfo : SpellbookComponent->GetPlayerSpells())
		{
			//Create the name of the widget using the following format: PlayerSpellSlot_[ArrayIndex]_[SpellInfo->Name] e.g. PlayerSpellSlot_1_Fireball
			FString SlotName = "PlayerSpellSlot_";
			SlotName.Append(UKismetStringLibrary::Conv_IntToString(ArrayIndex));
			SlotName.Append("_");
			SlotName.Append(UKismetStringLibrary::Conv_NameToString(SpellInfo->Name));

			//Create a SpellbookSlot widget, and add it as a child to the Player Slots wrap box
			if (USigilUISpellbookSlot* SpellbookSlot = CreateWidget<USigilUISpellbookSlot>(this, SpellbookSlotWidgetBP, UKismetStringLibrary::Conv_StringToName(SlotName)))
			{
				//Call SetInitialVariables for the new widget
				SpellbookSlot->SetInitialVariables(SpellInfo, this);

				//Make the new widget a child of the wrap box
				WrapBox_SpellbookPlayerSlots->AddChildToWrapBox(SpellbookSlot);

				//Increment ArrayIndex
				ArrayIndex++;
			}
		}
	}
}

FText USigilMenuSpellbook::Get_EditableTextBox_SpellName_HintText()
{
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//Set the text of EditableTextBox_SpellName to the value of SelectedSpell's Name variable
		return UKismetTextLibrary::Conv_NameToText(SelectedSpell->Name);
	}

	//Return nothing if validation fails
	return FText();
}

FText USigilMenuSpellbook::Get_EditableTextBox_Potency_HintText()
{
	//Hardcoded hint text to warn against entering non-numeric values
	return UKismetTextLibrary::Conv_StringToText("Numerical values only...");
}

void USigilMenuSpellbook::PopulateComboBoxes()
{
	ClearComboBoxes();

	//For each value in ESpellForm
	for (ESpellForm SpellForm : TEnumRange<ESpellForm>())
	{
		//Add the value as an option to the Spell Form combo box
		ComboBoxString_PropertySpellForm->AddOption(UEnum::GetDisplayValueAsText(SpellForm).ToString());

		//Add the value to the SpellFormTypes array
		SpellFormTypes.AddUnique(SpellForm);
	}

	//For each value in ESpellTarget
	for (ESpellTarget SpellTarget : TEnumRange<ESpellTarget>())
	{
		//Add the value as an option to the Target combo box
		ComboBoxString_PropertyTarget->AddOption(UEnum::GetDisplayValueAsText(SpellTarget).ToString());
		
		//Add the value to the SpellTargetTypes array
		SpellTargetTypes.AddUnique(SpellTarget);
	}
	
	//For each value in EMagicElement
	for (EMagicElementType MagicElement : TEnumRange<EMagicElementType>())
	{
		//Add the value as an option to the Element combo box
		ComboBoxString_PropertyElement->AddOption(UEnum::GetDisplayValueAsText(MagicElement).ToString());
		
		//Add the value to the MagicElementTypes array
		MagicElementTypes.AddUnique(MagicElement);
	}
}

void USigilMenuSpellbook::ClearComboBoxes()
{
	ComboBoxString_PropertySpellForm->ClearOptions();
	ComboBoxString_PropertyTarget->ClearOptions();
	ComboBoxString_PropertyElement->ClearOptions();
}

void USigilMenuSpellbook::ConvertSliderValues()
{
	//Pass the value of the MPCostPercent slider into ConvertPercentageToFloat. Set NewSpell.MPCostMultiplier to the function's output
	NewSpell.MPCostMultiplier = ConvertPercentageToFloat(Slider_MPCostPercent->GetSliderValue());

	//Pass the value of the DamagePercent slider into ConvertPercentageToFloat. Set NewSpell.DamageMultiplier to the function's output
	NewSpell.DamageMultiplier = ConvertPercentageToFloat(Slider_DamagePercent->GetSliderValue());

	//Pass the value of the SpeedPercent slider into ConvertPercentageToFloat. Set NewSpell.SpeedMultiplier to the function's output
	NewSpell.SpeedMultiplier = ConvertPercentageToFloat(Slider_SpeedPercent->GetSliderValue());
}

void USigilMenuSpellbook::ClearAllWrapBoxSlots()
{
	WrapBox_SpellbookCoreSlots->ClearChildren();
	WrapBox_SpellbookPlayerSlots->ClearChildren();
}

bool USigilMenuSpellbook::SearchWrapBoxForSelectedSpell(UWrapBox* InWrapBox)
{
	//If InWrapBox has children
	if (InWrapBox->HasAnyChildren())
	{
		//For each child of InWrapBox
		for (size_t i = 0; i < InWrapBox->GetChildrenCount(); i++)
		{
			//Try to cast it to USigilUISpellbookSlot
			if (USigilUISpellbookSlot* ChildSlot = Cast<USigilUISpellbookSlot>(InWrapBox->GetChildAt(i)))
			{
				//If the child's SlotSpellInfo is the same as SelectedSpell
				if (ChildSlot->SlotSpellInfo == SelectedSpell)
				{
					//Call SetNewSelectedSlot with ChildSlot as NewSlot
					SetNewSelectedSlot(ChildSlot);

					//Return true to show that this function found a matching spell
					return true;
				}
			}
		}
	}

	//Return false to show that this function did not find a matching spell
	return false;
}

void USigilMenuSpellbook::SetWidgetMinimumSize()
{
	WidgetMinimumWidth = Spellbook->MinDesiredWidth;
	WidgetMinimumHeight = Spellbook->MinDesiredHeight;
}



void USigilMenuSpellbook::ShowSpellProperties()
{
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		
		if (EditableTextBox_SpellName)
		{
			//Set the text of the SpellName text box to the Name of SelectedSpell
			EditableTextBox_SpellName->SetText(UKismetTextLibrary::Conv_NameToText(SelectedSpell->Name));
		}

		if (ComboBoxString_PropertySpellForm)
		{
			//Set the selected option of the SpellForm combo box to the Form of SelectedSpell
			ComboBoxString_PropertySpellForm->SetSelectedOption(UEnum::GetDisplayValueAsText(SelectedSpell->Form).ToString());
		}

		if (Slider_MPCostPercent)
		{
			//Get MPCostMultiplier from SelectedSpell and pass it into the function ConvertFloatToPercentage. Set the value of the MPCostPercent slider to the function's output.
			Slider_MPCostPercent->SetSliderValue(ConvertFloatToPercentage(SelectedSpell->MPCostMultiplier));
		}

		if (Slider_DamagePercent)
		{
			//Get DamageMultiplier from SelectedSpell and pass it into the function ConvertFloatToPercentage. Set the value of the DamagePercent slider to the function's output.
			Slider_DamagePercent->SetSliderValue(ConvertFloatToPercentage(SelectedSpell->DamageMultiplier));
		}

		if (Slider_SpeedPercent)
		{
			//Get SpeedMultiplier from SelectedSpell and pass it into the function ConvertFloatToPercentage. Set the value of the SpeedPercent slider to the function's output.
			Slider_SpeedPercent->SetSliderValue(ConvertFloatToPercentage(SelectedSpell->SpeedMultiplier));
		}

		if (CheckBox_Homing)
		{
			//Set IsChecked on the Homing check box to the value of IsHoming from SelectedSpell
			CheckBox_Homing->SetIsChecked(SelectedSpell->bIsHoming);
		}

		if (ComboBoxString_PropertyTarget)
		{
			//Set the selected option of the Target combo box to the Target of SelectedSpell
			ComboBoxString_PropertyTarget->SetSelectedOption(UEnum::GetDisplayValueAsText(SelectedSpell->Target).ToString());
		}

		if (ComboBoxString_PropertyElement)
		{
			//Set the selected option of the Element combo box to the ElementType of SelectedSpell's BaseSpellDamage first element
			ComboBoxString_PropertyElement->SetSelectedOption(UEnum::GetDisplayValueAsText(SelectedSpell->SpellDamage[0].ElementType).ToString());
		}

		if (EditableTextBox_Potency)
		{
			//Set the text of the Potency text box to DamageAmount from the same element
			EditableTextBox_Potency->SetText(UKismetTextLibrary::Conv_FloatToText(SelectedSpell->BaseSpellDamage[0].DamageAmount, ERoundingMode::HalfToEven));
		}

		if (Button_SaveChanges)
		{
			if (Button_DeleteSpell)
			{
				//If CanEdit from SelectedSpell equals true
				if (SelectedSpell->bCanEdit)
				{
					//Change the colour of the SaveChangesand DeleteSpell buttons to white
					Button_SaveChanges->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
					Button_DeleteSpell->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
				}
				else
				{
					//If false, make them dark grey
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
	if (SelectedSpell)
	{
		NewSpell = SelectedSpell->GetSpellProperties();
	}

	if (EditableTextBox_SpellName)
	{
		//Set NewSpellName to the text of the SpellName text box
		NewSpell.Name = UKismetStringLibrary::Conv_StringToName(EditableTextBox_SpellName->GetText().ToString());
	}

	if (ComboBoxString_PropertySpellForm)
	{
		//Set NewSpellForm to the selected option of the SpellForm combo box
		int SelectedIndex = UKismetMathLibrary::Clamp(ComboBoxString_PropertySpellForm->GetSelectedIndex(), 0, SpellFormTypes.Num() - 1);
		NewSpell.Form = SpellFormTypes[SelectedIndex];
	}

	//Call ConvertSliderValues
	ConvertSliderValues();

	if (CheckBox_Homing)
	{
		//Set NewSpellIsHoming to the value of IsChecked from the Homing check box
		NewSpell.bIsHoming = CheckBox_Homing->IsChecked();
	}

	if (ComboBoxString_PropertyTarget)
	{
		//Set NewSpellSpellTarget to the selected option of the Target combo box
		int SelectedIndex = UKismetMathLibrary::Clamp(ComboBoxString_PropertyTarget->GetSelectedIndex(), 0, SpellTargetTypes.Num() - 1);
		NewSpell.Target = SpellTargetTypes[SelectedIndex];
	}

	FSpellElements NewSpellElements;

	if (ComboBoxString_PropertyElement)
	{
		//Set NewSpellSpellElement to the selected option of the Element combo box
		int SelectedIndex = UKismetMathLibrary::Clamp(ComboBoxString_PropertyElement->GetSelectedIndex(), 0, MagicElementTypes.Num() - 1);
		NewSpellElements.ElementType = MagicElementTypes[SelectedIndex];
	}

	if (EditableTextBox_Potency)
	{
		//Set NewSpellPotency to the text of the Potency text box if the value is numeric
		if (UKismetStringLibrary::IsNumeric(EditableTextBox_Potency->GetText().ToString()))
		{
			NewSpellElements.DamageAmount = UKismetStringLibrary::Conv_StringToFloat(EditableTextBox_Potency->GetText().ToString());
		}
	}

	NewSpell.BaseSpellDamage.Empty();
	NewSpell.BaseSpellDamage.Add(NewSpellElements);
}

void USigilMenuSpellbook::AddSpellToSpellbar()
{
	//Cast the owning player controller to SigilPlayerController
	if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		//Validate SelectedSpell
		if (SelectedSpell)
		{
			//Call AddSpellToSpellbar from SigilPlayerController, passing SelectedSpell as the argument
			//PC->AddSpellToSpellbar(SelectedSpell);
			Cast<ASigilCharacter>(PC->GetPawn())->GetSpellcastingComponent()->AddNewPreparedSpell(SelectedSpell);

			PC->RequestRefreshSpellBar();
		}
	}
}

void USigilMenuSpellbook::CopySelectedSpell()
{
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//Create a new SpellInfo object
		UDA_SpellInfo* CopiedSpell = NewObject<UDA_SpellInfo>(this);

		if (SpellMap)
		{
			CopiedSpell->SpellMap = SpellMap;
		}

		//Give the new object the same spell properties as SelectedSpell
		CopiedSpell->SetSpellProperties(SelectedSpell->GetSpellProperties());
		
		//Rename the copied spell
		FString NewName = "Copy of ";
		NewName.Append(SelectedSpell->Name.ToString());
		CopiedSpell->Name = UKismetStringLibrary::Conv_StringToName(NewName);

		//Set bCanEdit to true
		CopiedSpell->bCanEdit = true;

		//Add the copied spell to the player's Spellbook
		if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
		{
			SC->GetSpellcastingComponent()->GetSpellbookComponent()->AddSpellToSpellbook(CopiedSpell);
		}
		

		//Set the copied spell as the selected spell
		SelectedSpell = CopiedSpell;

		//Refresh the widget
		RefreshSpellbookSlots();
	}
}

void USigilMenuSpellbook::CreateNewSpell()
{
	//Create a new SpellInfo object
	UDA_SpellInfo* CreatedSpell = NewObject<UDA_SpellInfo>(this);

	if (SpellMap)
	{
		CreatedSpell->SpellMap = SpellMap;
	}

	//Set bCanEdit to true
	CreatedSpell->bCanEdit = true;

	//Set the spell's properties using NewSpellDefaultProperties which is defined in blueprint
	CreatedSpell->SetSpellProperties(NewSpellDefaultProperties);

	//Add the new spell to the player's Spellbook
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayer()->GetPawn()))
	{
		SC->GetSpellcastingComponent()->GetSpellbookComponent()->AddSpellToSpellbook(CreatedSpell);
	}

	//Set the created spell as the selected spell
	SelectedSpell = CreatedSpell;

	//Refresh the widget
	RefreshSpellbookSlots();
}

void USigilMenuSpellbook::DeleteSelectedSpell()
{
	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//Check that the spell can be edited before proceeding
		if (SelectedSpell->bCanEdit)
		{
			//Cast the owning player controller's pawn to SigilCharacter
			if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
			{
				if (ASigilCharacter* SC = Cast<ASigilCharacter>(PC->GetPawn()))
				{
					//Remove the spell from the player's spellbook component
					if (SC->GetSpellcastingComponent()->GetSpellbookComponent()->RemoveSpellFromSpellbook(SelectedSpell))
					{
						RemoveSelectedSpellFromSpellbar();

						PC->RequestRefreshSpellBar();
					}
				}
			}
			

			RefreshSpellbookSlots();
		}
	}
}

void USigilMenuSpellbook::RemoveSelectedSpellFromSpellbar()
{
	//Cast the owning player controller to SigilPlayerController
	if (ASigilPlayerController* PC = Cast<ASigilPlayerController>(GetOwningPlayer()))
	{
		//Validate SelectedSpell
		if (SelectedSpell)
		{
			//Remove the spell from the player's Spell Bar
			//PC->RemoveSpellFromSpellbar(SelectedSpell);
			Cast<ASigilCharacter>(PC->GetPawn())->GetSpellcastingComponent()->RemovePreparedSpell(SelectedSpell);

			PC->RequestRefreshSpellBar();
		}
	}
}

void USigilMenuSpellbook::SaveChangesToSpell()
{
	SetNewSpellProperties();

	//Validate SelectedSpell
	if (SelectedSpell)
	{
		//If the spell is editable
		if (SelectedSpell->bCanEdit)
		{
			//Overwrite the properties of the SelectedSpell with the values changed by the player
			SelectedSpell->SetSpellProperties(NewSpell);

			//Refresh the widget
			RefreshSpellbookSlots();
		}
	}
}
