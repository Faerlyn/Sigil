


#include "SigilSpellTooltipWidget.h"

void USigilSpellTooltipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Get_TextBlock_Name_Text();

	Get_TextBlock_Form_Text();

	Get_TextBlock_Target_Text();

	Get_TextBlock_MPCost_Text();

	Get_TextBlock_Speed_Text();

	Get_TextBlock_Damage_Text();

	Get_TextBlock_Damage_ColorAndOpacity();

	CreateMeshCaptureActor();

	Get_Image_SpellPreview_Brush();
}

void USigilSpellTooltipWidget::NativeDestruct()
{
	
	DestroyMeshCaptureActor();

	Super::Destruct();

	
}

void USigilSpellTooltipWidget::Get_Image_SpellPreview_Brush()
{
	//If MadeBySpellbook is true, set the image of SpellPreview to BP_SpellbookRender_Mat. If false, set it to BP_SpellMeshRender_Mat.
	if (bMadeBySpellbook)
	{
		Image_SpellPreview->SetBrushResourceObject(SpellbookRenderMaterial);
	}
	else
	{
		Image_SpellPreview->SetBrushResourceObject(SpellRenderMaterial);
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_Name_Text()
{
	if (SpellRef)
	{
		TextBlock_Name->SetText(UKismetTextLibrary::Conv_NameToText(SpellRef->Name));
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_Form_Text()
{
	if (SpellRef)
	{
		TextBlock_Form->SetText(UEnum::GetDisplayValueAsText(SpellRef->Form));
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_Target_Text()
{
	if (SpellRef)
	{
		TextBlock_Target->SetText(UEnum::GetDisplayValueAsText(SpellRef->Target));
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_MPCost_Text()
{
	if (SpellRef)
	{
		TextBlock_MPCost->SetText(UKismetTextLibrary::Conv_FloatToText(SpellRef->MPCost, ERoundingMode::HalfToEven));
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_Speed_Text()
{
	if (SpellRef)
	{
		TextBlock_Speed->SetText(UKismetTextLibrary::Conv_FloatToText(SpellRef->Speed, ERoundingMode::HalfToEven));
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_Damage_Text()
{
	if (SpellRef)
	{
		FString DamageString;
		
		DamageString.Append(UKismetTextLibrary::Conv_FloatToText(SpellRef->SpellDamage[0].DamageAmount, ERoundingMode::HalfToEven).ToString());
		DamageString.Append(" (");
		DamageString.Append(UEnum::GetDisplayValueAsText(SpellRef->SpellDamage[0].ElementType).ToString());
		DamageString.Append(")");

		TextBlock_Damage->SetText(UKismetTextLibrary::Conv_StringToText(DamageString));
	}
}

void USigilSpellTooltipWidget::Get_TextBlock_Damage_ColorAndOpacity()
{
	/*Get the first element of SpellRef's SpellDamage array. Try to find the value of ColourMap using ElementType as the key. If a value is found, set NewTextColour to equal 
	this value and pass it into the return node*/
	if (SpellRef)
	{
		if (FLinearColor* value = ColourMap.Find(SpellRef->SpellDamage[0].ElementType))
		{
			TextBlock_Damage->SetColorAndOpacity(FSlateColor(*value));
		}
	}
	else
	{
		TextBlock_Damage->ColorAndOpacity = FSlateColor(FLinearColor(0.1f, 0.1f, 0.1f));
	}
}

void USigilSpellTooltipWidget::CreateMeshCaptureActor()
{
	if (APawn* PlayerPawn = GetOwningPlayer()->GetPawn())
	{
		const FTransform SpawnLocAndRotation(FRotator(0,0,0), PlayerPawn->GetActorLocation(),FVector3d(1,1,1));

		if (SpellRef)
		{
			if (SpellCaptureActorBP)
			{
				MeshCaptureRef = GetWorld()->SpawnActorDeferred<ASigilSpellCaptureActor>(SpellCaptureActorBP, SpawnLocAndRotation);
				MeshCaptureRef->SetInitialVariables(SpellRef, bMadeBySpellbook);
				MeshCaptureRef->FinishSpawning(SpawnLocAndRotation);
			}
		}
	}
}

void USigilSpellTooltipWidget::DestroyMeshCaptureActor()
{
	if (MeshCaptureRef)
	{
		MeshCaptureRef->Destroy();
	}
}

void USigilSpellTooltipWidget::SetInitialVariables(UDA_SpellInfo* InSpellInfo, bool MadeBySpellbook)
{
	if (InSpellInfo)
	{
		SpellRef = InSpellInfo;
	}

	bMadeBySpellbook = MadeBySpellbook;
}
