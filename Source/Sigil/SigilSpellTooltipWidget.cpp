


#include "SigilSpellTooltipWidget.h"

void USigilSpellTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Bind textblock delegates
	TextBlock_Name->TextDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_Name_Text);
	TextBlock_Name->SynchronizeProperties();

	TextBlock_Form->TextDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_Form_Text);
	TextBlock_Form->SynchronizeProperties();

	TextBlock_Target->TextDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_Target_Text);
	TextBlock_Target->SynchronizeProperties();

	TextBlock_MPCost->TextDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_MPCost_Text);
	TextBlock_MPCost->SynchronizeProperties();

	TextBlock_Speed->TextDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_Speed_Text);
	TextBlock_Speed->SynchronizeProperties();

	TextBlock_Damage->TextDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_Damage_Text);
	TextBlock_Damage->SynchronizeProperties();

	TextBlock_Damage->ColorAndOpacityDelegate.BindDynamic(this, &USigilSpellTooltipWidget::Get_TextBlock_Damage_ColorAndOpacity);
	TextBlock_Damage->SynchronizeProperties();

	CreateMeshCaptureActor();

	Get_Image_SpellPreview_Brush();

	//Validate Anim_ButtonPressed
	if (Anim_FadeIn)
	{
		//Play the button pressed animation
		PlayAnimation(Anim_FadeIn, 0, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
	}
}

void USigilSpellTooltipWidget::NativeDestruct()
{
	//Destrory the spawned MeshCaptureActor when the tooltip is destructed
	DestroyMeshCaptureActor();

	Super::Destruct();
}

void USigilSpellTooltipWidget::Get_Image_SpellPreview_Brush()
{
	//If MadeBySpellbook is true
	if (bMadeBySpellbook)
	{
		//Set the image of SpellPreview to BP_SpellbookRender_Mat
		Image_SpellPreview->SetBrushResourceObject(SpellbookRenderMaterial);
	}
	else
	{
		//If false, set it to BP_SpellMeshRender_Mat.
		Image_SpellPreview->SetBrushResourceObject(SpellRenderMaterial);
	}
}

FText USigilSpellTooltipWidget::Get_TextBlock_Name_Text()
{
	if (SpellRef)
	{
		return UKismetTextLibrary::Conv_NameToText(SpellRef->Name);
	}

	return FText();
}

FText USigilSpellTooltipWidget::Get_TextBlock_Form_Text()
{
	if (SpellRef)
	{
		return UEnum::GetDisplayValueAsText(SpellRef->Form);
	}

	return FText();
}

FText USigilSpellTooltipWidget::Get_TextBlock_Target_Text()
{
	if (SpellRef)
	{
		return UEnum::GetDisplayValueAsText(SpellRef->Target);
	}

	return FText();
}

FText USigilSpellTooltipWidget::Get_TextBlock_MPCost_Text()
{
	if (SpellRef)
	{
		return UKismetTextLibrary::Conv_FloatToText(SpellRef->MPCost, ERoundingMode::HalfToEven);
	}

	return FText();
}

FText USigilSpellTooltipWidget::Get_TextBlock_Speed_Text()
{
	if (SpellRef)
	{
		return UKismetTextLibrary::Conv_FloatToText(SpellRef->Speed, ERoundingMode::HalfToEven);
	}

	return FText();
}

FText USigilSpellTooltipWidget::Get_TextBlock_Damage_Text()
{
	if (SpellRef)
	{
		//Format the text as follows: "[DamageAmount] ([ElementType])" e.g. 10 (Water)
		FString DamageString;
		
		DamageString.Append(UKismetTextLibrary::Conv_FloatToText(SpellRef->SpellDamage[0].DamageAmount, ERoundingMode::HalfToEven).ToString());
		DamageString.Append(" (");
		DamageString.Append(UEnum::GetDisplayValueAsText(SpellRef->SpellDamage[0].ElementType).ToString());
		DamageString.Append(")");

		return UKismetTextLibrary::Conv_StringToText(DamageString);
	}

	//Return nothing if validation fails
	return FText();
}

FSlateColor USigilSpellTooltipWidget::Get_TextBlock_Damage_ColorAndOpacity()
{
	//Validate SpellRef
	if (SpellRef)
	{
		//Get the first element of SpellRef's SpellDamage array and try to find the value of ColourMap using ElementType as the key.
		if (FLinearColor* value = ColourMap.Find(SpellRef->SpellDamage[0].ElementType))
		{
			//If a value is found, set the colour of the text to this value
			return FSlateColor(*value);
		}
	}
	
	//Make the text this colour if validation fails
	return FSlateColor(FLinearColor(0.1f, 0.1f, 0.1f));
}

void USigilSpellTooltipWidget::CreateMeshCaptureActor()
{
	//Get the owning player controller's pawn
	if (APawn* PlayerPawn = GetOwningPlayer()->GetPawn())
	{
		//Get the location and rotation of the pawn
		const FTransform SpawnLocAndRotation(FRotator(0,0,0), PlayerPawn->GetActorLocation(),FVector3d(1,1,1));

		//Validate SpellRef
		if (SpellRef)
		{
			//Validate SpellCaptureActorBP
			if (SpellCaptureActorBP)
			{
				//Create an actor of class ASigilSpellCaptureActor using the location and rotation of the player's pawn
				MeshCaptureRef = GetWorld()->SpawnActorDeferred<ASigilSpellCaptureActor>(SpellCaptureActorBP, SpawnLocAndRotation);

				//Call SetInitialVariables from MeshCaptureRef before spawning the actor
				MeshCaptureRef->SetInitialVariables(SpellRef, bMadeBySpellbook);

				//Finish spawning the actor
				MeshCaptureRef->FinishSpawning(SpawnLocAndRotation);
			}
		}
	}
}

void USigilSpellTooltipWidget::DestroyMeshCaptureActor()
{
	//If MeshCaptureRef is valid
	if (MeshCaptureRef)
	{
		//Destroy the actor
		MeshCaptureRef->Destroy();
	}
}

/// <summary>
/// This function needs to be called for the tooltip to function as intended
/// </summary>
/// <param name="InSpellInfo">A pointer to a UDA_SpellInfo object, information from this object is displayed by this widget</param>
/// <param name="MadeBySpellbook">This determines which material is used when we set the BrushResourceObject</param>
void USigilSpellTooltipWidget::SetInitialVariables(UDA_SpellInfo* InSpellInfo, bool MadeBySpellbook)
{
	if (InSpellInfo)
	{
		SpellRef = InSpellInfo;
	}

	bMadeBySpellbook = MadeBySpellbook;
}
