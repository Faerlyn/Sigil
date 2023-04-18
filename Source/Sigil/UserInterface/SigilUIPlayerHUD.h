

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilUIPlayerHUD.generated.h"

class UImage;

class USigilUICharacterAttributeBars;
class USigilMenuSelectionBar;
class USigilUITargetLock;

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUIPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "Player HUD | Widgets")
		UImage* Image_Crosshair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "Player HUD | Widgets")
		USigilUICharacterAttributeBars* Widget_CharacterAttributeBars;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "Player HUD | Widgets")
		USigilMenuSelectionBar* Widget_SpellSelectionBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), Category = "Player HUD | Widgets")
		USigilUITargetLock* Widget_TargetLock;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	//Getter for Widget_SpellSelectionBar
	UFUNCTION(BlueprintCallable, Category = "Player HUD | Widgets")
		USigilMenuSelectionBar* GetSpellSelectionBarWidget();

	//Getter for Widget_TargetLock
	UFUNCTION(BlueprintCallable, Category = "Player HUD | Widgets")
		USigilUITargetLock* GetTargetLockWidget();
};
