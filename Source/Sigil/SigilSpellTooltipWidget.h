

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UDA_SpellInfo.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SigilSpellCaptureActor.h"
#include "Kismet/KismetTextLibrary.h"
#include "SigilSpellTooltipWidget.generated.h"

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
		void Get_TextBlock_Name_Text();

	UFUNCTION(BlueprintCallable)
		void Get_TextBlock_Form_Text();

	UFUNCTION(BlueprintCallable)
		void Get_TextBlock_Target_Text();

	UFUNCTION(BlueprintCallable)
		void Get_TextBlock_MPCost_Text();

	UFUNCTION(BlueprintCallable)
		void Get_TextBlock_Speed_Text();

	UFUNCTION(BlueprintCallable)
		void Get_TextBlock_Damage_Text();

	UFUNCTION(BlueprintCallable)
		void Get_TextBlock_Damage_ColorAndOpacity();

	UFUNCTION()
		void CreateMeshCaptureActor();

	UFUNCTION()
		void DestroyMeshCaptureActor();

public:

	UFUNCTION()
		void SetInitialVariables(UDA_SpellInfo* InSpellInfo, bool MadeBySpellbook);

};
