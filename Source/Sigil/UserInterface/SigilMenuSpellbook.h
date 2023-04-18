

#pragma once

#include "CoreMinimal.h"
#include "SigilMenuWidgetBase.h"
#include "../Library/Struct/SpellStructs.h"
#include "SigilMenuSpellbook.generated.h"

class UCheckBox;
class UComboBoxString;
class UEditableTextBox;
class UScaleBox;
class USizeBox;
class UWrapBox;

class UDA_SpellInfo;
class UDA_SpellMap;
class USigilSpellTooltipWidget;
class USigilUIButtonBasic;
class USigilUIPercentageSlider;
class USigilUISpellbookSlot;
class USigilUISpellSlot;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilMenuSpellbook : public USigilMenuWidgetBase
{
	GENERATED_BODY()
	
public:

protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		USizeBox* Spellbook;

	UPROPERTY(meta = (BindWidget))
		USigilUIButtonBasic* Button_AddToSpellbar;

	UPROPERTY(meta = (BindWidget))
		USigilUIButtonBasic* Button_CopySpell;

	UPROPERTY(meta = (BindWidget))
		USigilUIButtonBasic* Button_DeleteSpell;

	UPROPERTY(meta = (BindWidget))
		USigilUIButtonBasic* Button_NewSpell;

	UPROPERTY(meta = (BindWidget))
		USigilUIButtonBasic* Button_RemoveFromSpellbar;

	UPROPERTY(meta = (BindWidget))
		USigilUIButtonBasic* Button_SaveChanges;

	UPROPERTY(meta = (BindWidget))
		UScaleBox* ScaleBox_Tooltip;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | Reference")
		USigilSpellTooltipWidget* TooltipRef;

	UPROPERTY(EditAnywhere, Category = "Spellbook | Reference")
		TSubclassOf<USigilSpellTooltipWidget> SpellTooltipWidgetBP;

	UPROPERTY(EditAnywhere, Category = "Spellbook | Reference")
		TSubclassOf<USigilUISpellSlot> SpellbookSlotWidgetBP;

	UPROPERTY(meta = (BindWidget))
		UWrapBox* WrapBox_SpellbookCoreSlots;

	UPROPERTY(meta = (BindWidget))
		UWrapBox* WrapBox_SpellbookPlayerSlots;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | Reference")
		USigilUISpellbookSlot* SelectedSlot;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* CheckBox_Homing;

	UPROPERTY(meta = (BindWidget))
		UComboBoxString* ComboBoxString_PropertyElement;

	UPROPERTY(meta = (BindWidget))
		UComboBoxString* ComboBoxString_PropertySpellForm;

	UPROPERTY(meta = (BindWidget))
		UComboBoxString* ComboBoxString_PropertyTarget;

	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* EditableTextBox_SpellName;

	UPROPERTY(meta = (BindWidget))
		UEditableTextBox* EditableTextBox_Potency;

	UPROPERTY(meta = (BindWidget))
		USigilUIPercentageSlider* Slider_MPCostPercent;
	
	UPROPERTY(meta = (BindWidget))
		USigilUIPercentageSlider* Slider_DamagePercent;

	UPROPERTY(meta = (BindWidget))
		USigilUIPercentageSlider* Slider_SpeedPercent;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | Reference")
		UDA_SpellInfo* SelectedSpell;

	UPROPERTY(VisibleAnywhere)
		TArray<ESpellForm> SpellFormTypes;

	UPROPERTY(VisibleAnywhere)
		TArray<ESpellTarget> SpellTargetTypes;

	UPROPERTY(VisibleAnywhere)
		TArray<EMagicElementType> MagicElementTypes;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		FSpellProperties NewSpell;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		FName NewSpell_Name;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		ESpellForm NewSpell_Form;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		float NewSpell_MPCostMultiplier;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		float NewSpell_DamageMultiplier;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		float NewSpell_SpeedMultiplier;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		bool bNewSpell_IsHoming;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		ESpellTarget NewSpell_Target;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		EMagicElementType NewSpell_MagicElement;

	UPROPERTY(VisibleAnywhere, Category = "Spellbook | New Spell")
		float NewSpell_Potency;

	UPROPERTY(EditAnywhere, Category = "Spellbook | New Spell Defaults")
		FSpellProperties NewSpellDefaultProperties;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spellbook | New Spell Defaults")
		UDA_SpellMap* SpellMap;

	/// <summary>
	/// <para>Converts a float value between 0 and 2 into a percentage value used by this widget's sliders.</para>
	/// E.g. 0.2 -> -80%, 1.5 -> +50%
	/// </summary>
	/// <param name="InValue">The float value to convert</param>
	/// <returns></returns>
	float ConvertFloatToPercentage(float InValue);

	/// <summary>
	/// <para>Converts a float value between -100 and 100 into the float value used by DA_SpellInfo's multiplier variables.</para>
	/// E.g. -80 -> 0.2, 50 -> 1.5
	/// </summary>
	/// <param name="InValue">The float value to convert</param>
	/// <returns></returns>
	float ConvertPercentageToFloat(float InValue);

	// Update the tooltip shown in the Spellbook widget
	void CreateSpellbookTooltipWidget();


	// Calls various functions to update the Spellbook widget
	void RefreshSpellbookSlots();

	// If SelectedSpell is valid, search the Core and Player Slot WrapBoxes for SelectedSpell. If it is found, set its SpellbookSlot as the new selected slot
	void SetSelectedSlot();

	// Creates USigilUISpellbookSlot widgets to put inside the CoreSlots WrapBox. The widgets are created from UDA_SpellInfo objects found by the Asset Registry.
	void PopulateCoreSlots();

	/// <summary>
	/// Creates USigilUISpellbookSlot widgets to put inside the CoreSlots wrap box.
	/// The widgets are created from UDA_SpellInfo objects stored in the player character's PlayerSpells array.
	/// </summary>
	void PopulatePlayerSlots();

	UFUNCTION()
		FText Get_EditableTextBox_SpellName_HintText();

	UFUNCTION()
		FText Get_EditableTextBox_Potency_HintText();

	// Populates the options of the combo boxes used this widget
	void PopulateComboBoxes();

	// Clears the options from this widget's combo boxes
	void ClearComboBoxes();

	// Calls ConvertPercentageToFloat for each slider widget and sets NewSpell's multiplier variables
	void ConvertSliderValues();

	// Remove any child objects from the wrap boxes
	void ClearAllWrapBoxSlots();

	/// <summary>
	/// This function gets the children of InWrapBox and casts them to USigilUISpellbookSlot.
	/// If the SlotSpellInfo variable of a child object is the same as SelectedSpell, return true.
	/// </summary>
	/// <param name="InWrapBox">The WrapBox to search through</param>
	/// <returns>true or false</returns>
	bool SearchWrapBoxForSelectedSpell(UWrapBox* InWrapBox);

	// Set this widget's minimum height and width, these two variables will be used by the WindowFrame widget
	void SetWidgetMinimumSize();

	// Updates the information displayed in the spell properties vertical box
	void ShowSpellProperties();

	// Populate NewSpell's properties so that it can overwrite the selected spell when the player clicks save changes.
	void SetNewSpellProperties();

	// Adds the selected spell to the spellbar at the bottom of the player's screen
	UFUNCTION()
	void AddSpellToSpellbar();

	// Creates a copy of the selected spell for the player to edit
	UFUNCTION()
	void CopySelectedSpell();	

	// Creates a UDA_SpellInfo object with the default properties defined in this widget's blueprint
	UFUNCTION()
	void CreateNewSpell();

	// Deletes the selected UDA_SpellInfo object if it is editable
	UFUNCTION()
	void DeleteSelectedSpell();

	// Removes the selected spell from the spellbar at the bottom of the player's screen
	UFUNCTION()
	void RemoveSelectedSpellFromSpellbar();

	// Overwrites the FSpellProperties of the currently selected spell with NewSpell
	UFUNCTION()
	void SaveChangesToSpell();

public:

	/// <summary>
	/// Sets NewSlot as the new selected slot and updates the information displayed by the Spellbook widget
	/// </summary>
	/// <param name="NewSlot">The widget that will be set as the new selected slot</param>
	void SetNewSelectedSlot(USigilUISpellbookSlot* NewSlot);


};
