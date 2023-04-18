


#include "SigilUICharacterAttributeBars.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

#include "../Actor/Character/SigilCharacter.h"
#include "../Actor/Component/CharacterAttributesComponent.h"


void USigilUICharacterAttributeBars::NativeConstruct()
{
	//Get the owning player pawn and cast it to SigilCharacter
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwningPlayerPawn()))
	{
		//Set CharacterAttributesRef to SigilCharacter's CharacterAttributesComponent
		CharacterAttributesRef = SC->GetCharacterAttributesComponent();
	}

	//Validate ProgressBar_HP
	if (ProgressBar_HP)
	{
		//Bind delegates
		ProgressBar_HP->PercentDelegate.BindDynamic(this, &USigilUICharacterAttributeBars::Get_ProgressBar_HP_Percent);
		ProgressBar_HP->SynchronizeProperties();
	}

	//Validate ProgressBar_MP
	if (ProgressBar_MP)
	{
		//Bind delegates
		ProgressBar_MP->PercentDelegate.BindDynamic(this, &USigilUICharacterAttributeBars::Get_ProgressBar_MP_Percent);
		ProgressBar_MP->SynchronizeProperties();
	}

	//Validate ProgressBar_SP
	if (ProgressBar_SP)
	{
		//Bind delegates
		ProgressBar_SP->PercentDelegate.BindDynamic(this, &USigilUICharacterAttributeBars::Get_ProgressBar_SP_Percent);
		ProgressBar_SP->SynchronizeProperties();
	}

	//Validate TextBlock_HitPoints
	if (TextBlock_HitPoints)
	{
		//Bind delegates
		TextBlock_HitPoints->TextDelegate.BindDynamic(this, &USigilUICharacterAttributeBars::Get_TextBlock_HitPoints_Text);
		TextBlock_HitPoints->SynchronizeProperties();
	}

	//Validate TextBlock_MagicPoints
	if (TextBlock_MagicPoints)
	{
		//Bind delegates
		TextBlock_MagicPoints->TextDelegate.BindDynamic(this, &USigilUICharacterAttributeBars::Get_TextBlock_MagicPoints_Text);
		TextBlock_MagicPoints->SynchronizeProperties();
	}

	//Validate TextBlock_StaminaPoints
	if (TextBlock_StaminaPoints)
	{
		//Bind delegates
		TextBlock_StaminaPoints->TextDelegate.BindDynamic(this, &USigilUICharacterAttributeBars::Get_TextBlock_StaminaPoints_Text);
		TextBlock_StaminaPoints->SynchronizeProperties();
	}
	
}

float USigilUICharacterAttributeBars::Get_ProgressBar_HP_Percent()
{
	//Validate CharacterAttributesRef
	if (CharacterAttributesRef)
	{
		//Divide the current hit points by the maximum hit points to get the player character's HP value as a percentage (0 = 0%, 0.5 = 50%, 1 = 100% etc.)
		return CharacterAttributesRef->GetCurrentHitPoints() / CharacterAttributesRef->GetMaximumHitPoints();
	}

	return 0.0f;
}

float USigilUICharacterAttributeBars::Get_ProgressBar_MP_Percent()
{
	//Validate CharacterAttributesRef
	if (CharacterAttributesRef)
	{
		//Divide the current magic points by the maximum magic points to get the player character's MP value as a percentage (0 = 0%, 0.5 = 50%, 1 = 100% etc.)
		return CharacterAttributesRef->GetCurrentMagicPoints() / CharacterAttributesRef->GetMaximumMagicPoints();
	}

	return 0.0f;
}

float USigilUICharacterAttributeBars::Get_ProgressBar_SP_Percent()
{
	//Validate CharacterAttributesRef
	if (CharacterAttributesRef)
	{
		//Divide the current hitpoints by the maximum hitpoints to get the player character's SP value as a percentage (0 = 0%, 0.5 = 50%, 1 = 100% etc.)
		return CharacterAttributesRef->GetCurrentStaminaPoints() / CharacterAttributesRef->GetMaximumStaminaPoints();
	}

	return 0.0f;
}

FText USigilUICharacterAttributeBars::Get_TextBlock_HitPoints_Text()
{
	//Validate CharacterAttributesRef
	if (CharacterAttributesRef)
	{
		/*	Display the player's hit points in the following format:
			CurrentHP / MaximumHP
			e.g. 50 / 100	*/

		FString AttributeString;
		
		AttributeString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(CharacterAttributesRef->GetCurrentHitPoints())));
		AttributeString.Append(" / ");
		AttributeString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(CharacterAttributesRef->GetMaximumHitPoints())));

		//Return the completed string as text
		return UKismetTextLibrary::Conv_StringToText(AttributeString);
	}

	return FText();
}

FText USigilUICharacterAttributeBars::Get_TextBlock_MagicPoints_Text()
{
	//Validate CharacterAttributesRef
	if (CharacterAttributesRef)
	{
		/*	Display the player's magic points in the following format:
			CurrentMP / MaximumMP
			e.g. 50 / 100	*/

		FString AttributeString;

		AttributeString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(CharacterAttributesRef->GetCurrentMagicPoints())));
		AttributeString.Append(" / ");
		AttributeString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(CharacterAttributesRef->GetMaximumMagicPoints())));

		//Return the completed string as text
		return UKismetTextLibrary::Conv_StringToText(AttributeString);
	}

	return FText();
}

FText USigilUICharacterAttributeBars::Get_TextBlock_StaminaPoints_Text()
{
	//Validate CharacterAttributesRef
	if (CharacterAttributesRef)
	{
		/*	Display the player's stamina points in the following format:
			CurrentSP / MaximumSP
			e.g. 50 / 100	*/

		FString AttributeString;

		AttributeString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(CharacterAttributesRef->GetCurrentStaminaPoints())));
		AttributeString.Append(" / ");
		AttributeString.Append(UKismetStringLibrary::Conv_IntToString(UKismetMathLibrary::Round(CharacterAttributesRef->GetMaximumStaminaPoints())));

		//Return the completed string as text
		return UKismetTextLibrary::Conv_StringToText(AttributeString);
	}

	return FText();
}
