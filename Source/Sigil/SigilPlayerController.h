

#pragma once

#include "CoreMinimal.h"
#include "UDA_SpellInfo.h"
#include "GameFramework/PlayerController.h"
#include "SigilPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API ASigilPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void TogglePlayerMouseCursor(bool ShowCursor);

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AddSpellToSpellbar(UDA_SpellInfo* InSpellInfo);*/

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RemoveSpellFromSpellbar(UDA_SpellInfo* InSpellInfo);*/

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RequestRefreshSpellBar();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RequestSelectSpecificSlot(int SlotNumber);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void GetAllTargetableActorsOnScreen();

protected:


};
