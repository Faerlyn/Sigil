

#pragma once

#include "CoreMinimal.h"
#include "SigilMenuWidgetBase.h"
#include "Components/SizeBox.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/ScaleBox.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/Slider.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ScaleBoxSlot.h"
#include "SigilUISpellbookSlot.h"
#include "SigilSpellTooltipWidget.h"
#include "SigilUIPercentageSlider.h"
#include "SigilUIButtonBasic.h"
#include "SigilCharacter.h"
#include "SigilPlayerController.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "SigilMenuSpellbook.generated.h"

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

	float ConvertFloatToPercentage(float InValue);

	float ConvertPercentageToFloat(float InValue);

	void CreateSpellbookTooltipWidget();

	void RefreshSpellbookSlots();

	void SetSelectedSlot();

	void PopulateCoreSlots();

	void PopulatePlayerSlots();

	UFUNCTION()
		FText Get_EditableTextBox_SpellName_HintText();

	UFUNCTION()
		FText Get_EditableTextBox_Potency_HintText();

	void PopulateComboBoxes();

	void ClearComboBoxes();

	void ConvertSliderValues();

	void ClearAllWrapBoxSlots();

	bool SearchWrapBoxForSelectedSpell(UWrapBox* InWrapBox);
			
	void SetWidgetMinimumSize();
			
	void ShowSpellProperties();
			
	void SetNewSpellProperties();
			
	UFUNCTION()
	void AddSpellToSpellbar();

	UFUNCTION()
	void CopySelectedSpell();	

	UFUNCTION()
	void CreateNewSpell();

	UFUNCTION()
	void DeleteSelectedSpell();

	UFUNCTION()
	void RemoveSelectedSpellFromSpellbar();

	UFUNCTION()
	void SaveChangesToSpell();

public:

	void SetNewSelectedSlot(USigilUISpellbookSlot* NewSlot);


};
