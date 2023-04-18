

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilSpellTooltipWidget.generated.h"

class UImage;
class UTextBlock;

class ASigilSpellCaptureActor;
class UDA_SpellInfo;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilSpellTooltipWidget : public UUserWidget
{
	GENERATED_BODY()

public:


protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), Category = "Reference")
		UDA_SpellInfo* SpellRef;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient, Category = "Sigil Button | Animations")
		UWidgetAnimation* Anim_FadeIn = nullptr;

	UPROPERTY(EditAnywhere, Category = "Reference")
		TSubclassOf<ASigilSpellCaptureActor> SpellCaptureActorBP;

	UPROPERTY(VisibleAnywhere, Category = "Reference")
		ASigilSpellCaptureActor* MeshCaptureRef;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UImage* Image_SpellPreview;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UTextBlock* TextBlock_Damage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UTextBlock* TextBlock_Form;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UTextBlock* TextBlock_MPCost;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UTextBlock* TextBlock_Name;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UTextBlock* TextBlock_Speed;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Widget")
		UTextBlock* TextBlock_Target;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = "true", BlueprintVisible = "true"), VisibleAnywhere)
		bool bMadeBySpellbook;

	UPROPERTY(EditAnywhere)
		TMap<EMagicElementType, FLinearColor> ColourMap;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* SpellRenderMaterial;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* SpellbookRenderMaterial;

	UFUNCTION(BlueprintCallable)
		void Get_Image_SpellPreview_Brush();

	UFUNCTION(BlueprintCallable)
		FText Get_TextBlock_Name_Text();

	UFUNCTION(BlueprintCallable)
		FText Get_TextBlock_Form_Text();

	UFUNCTION(BlueprintCallable)
		FText Get_TextBlock_Target_Text();

	UFUNCTION(BlueprintCallable)
		FText Get_TextBlock_MPCost_Text();

	UFUNCTION(BlueprintCallable)
		FText Get_TextBlock_Speed_Text();

	UFUNCTION(BlueprintCallable)
		FText Get_TextBlock_Damage_Text();

	UFUNCTION(BlueprintCallable)
		FSlateColor Get_TextBlock_Damage_ColorAndOpacity();

	//Spawns a 3DRender actor that is used to display the spell projectile inside the tooltip
	UFUNCTION()
		void CreateMeshCaptureActor();

	//Destroys MeshCaptureRef
	UFUNCTION()
		void DestroyMeshCaptureActor();

public:

	/// <summary>
	/// This function needs to be called for the tooltip to function as intended
	/// </summary>
	/// <param name="InSpellInfo">A pointer to a UDA_SpellInfo object, information from this object is displayed by this widget</param>
	/// <param name="MadeBySpellbook">This determines which material is used when we set the BrushResourceObject</param>
	UFUNCTION()
		void SetInitialVariables(UDA_SpellInfo* InSpellInfo, bool MadeBySpellbook);

};
