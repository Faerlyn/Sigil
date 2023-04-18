


#include "SigilUIPlayerHUD.h"

#include "Components/Image.h"

#include "SigilUICharacterAttributeBars.h"
#include "SigilMenuSelectionBar.h"
#include "SigilUITargetLock.h"

void USigilUIPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	//Validate Widget_TargetLock
	if (Widget_TargetLock)
	{
		//Hide the widget when the game starts
		Widget_TargetLock->HideWidget();
	}
}

void USigilUIPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Validate Widget_TargetLock
	if (Widget_TargetLock)
	{
		//Call UpdateWidget
		Widget_TargetLock->UpdateWidget();
	}
}

USigilMenuSelectionBar* USigilUIPlayerHUD::GetSpellSelectionBarWidget()
{
	//Validate Widget_SpellSelectionBar
	if (Widget_SpellSelectionBar)
	{
		//Return Widget_SpellSelectionBar
		return Widget_SpellSelectionBar;
	}

	return nullptr;
}

USigilUITargetLock* USigilUIPlayerHUD::GetTargetLockWidget()
{
	//Validate Widget_TargetLock
	if (Widget_TargetLock)
	{
		//Return Widget_TargetLock
		return Widget_TargetLock;
	}

	return nullptr;
}
