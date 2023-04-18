

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilUICharacterAttributeBars.generated.h"

class UProgressBar;
class UTextBlock;

class UCharacterAttributesComponent;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUICharacterAttributeBars : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, Category = "Character Attribute Bars | References")
		UCharacterAttributesComponent* CharacterAttributesRef;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Character Attribute Bars | References")
		UProgressBar* ProgressBar_HP;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Character Attribute Bars | References")
		UProgressBar* ProgressBar_MP;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Character Attribute Bars | References")
		UProgressBar* ProgressBar_SP;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Character Attribute Bars | References")
		UTextBlock* TextBlock_HitPoints;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Character Attribute Bars | References")
		UTextBlock* TextBlock_MagicPoints;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Character Attribute Bars | References")
		UTextBlock* TextBlock_StaminaPoints;

	// Called when ProgressBar_HP's PercentDelegate is executed
	// Sets ProgressBar_HP's percent value
	UFUNCTION(BlueprintCallable, Category = "Character Attribute Bars | Progress Bar")
		float Get_ProgressBar_HP_Percent();

	// Called when ProgressBar_MP's PercentDelegate is executed
	// Sets ProgressBar_MP's percent value
	UFUNCTION(BlueprintCallable, Category = "Character Attribute Bars | Progress Bar")
		float Get_ProgressBar_MP_Percent();

	// Called when ProgressBar_SP's PercentDelegate is executed
	// Sets ProgressBar_SP's percent value
	UFUNCTION(BlueprintCallable, Category = "Character Attribute Bars | Progress Bar")
		float Get_ProgressBar_SP_Percent();

	// Called when TextBlock_HitPoints's TextDelegate is executed
	// Sets TextBlock_HitPoints's text value
	UFUNCTION(BlueprintCallable, Category = "Character Attribute Bars | Progress Bar")
		FText Get_TextBlock_HitPoints_Text();

	// Called when TextBlock_MagicPoints's TextDelegate is executed
	// Sets TextBlock_MagicPoints's text value
	UFUNCTION(BlueprintCallable, Category = "Character Attribute Bars | Progress Bar")
		FText Get_TextBlock_MagicPoints_Text();

	// Called when TextBlock_StaminaPoints's TextDelegate is executed
	// Sets TextBlock_StaminaPoints's text value
	UFUNCTION(BlueprintCallable, Category = "Character Attribute Bars | Progress Bar")
		FText Get_TextBlock_StaminaPoints_Text();

public:


};
