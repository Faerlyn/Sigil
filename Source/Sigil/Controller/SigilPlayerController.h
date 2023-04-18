

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "SigilPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

class USigilSaveGame;
class USigilMenuSpellbook;
class USigilUIPlayerHUD;
class USigilUITargetLock;
class USigilWindowFrame;

USTRUCT(BlueprintType)
struct FOnScreenTargetInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor* TargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName ActorName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DistanceToScreenCenter;
};

/**
 * 
 */
UCLASS()
class SIGIL_API ASigilPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Configure Player Input
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Sigil Player Controller | Player Data")
		FName PlayerName = "Sigil Player";

	UPROPERTY(VisibleAnywhere, Category = "Sigil Player Controller | Save Data")
		TSubclassOf<USigilSaveGame> SaveGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Player Controller | Save Data")
		USigilSaveGame* SaveGameRef;

	UPROPERTY(EditAnywhere, Category = "Sigil Player Controller | Save Data")
		FString SaveSlotName = "SigilPlayerSave";

	UPROPERTY(EditAnywhere, Category = "Sigil Player Controller | Player Widgets")
		TSubclassOf<USigilUIPlayerHUD> PlayerHUDWidgetBP;

	UPROPERTY(EditAnywhere, Category = "Sigil Player Controller | Player Widgets")
		TSubclassOf<USigilWindowFrame> WindowFrameWidgetBP;

	UPROPERTY(EditAnywhere, Category = "Sigil Player Controller | Player Widgets")
		TSubclassOf<USigilMenuSpellbook> SpellbookWidgetBP;

	UPROPERTY(BlueprintReadOnly, Category = "Sigil Player Controller | Player Widgets")
		USigilUIPlayerHUD* PlayerHUDWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Sigil Player Controller | Player Widgets")
		USigilWindowFrame* SpellbookWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Sigil Player Controller | Player Widgets")
		USigilUITargetLock* TargetLockWidget;
		
	UPROPERTY(VisibleAnywhere, Category = "Sigil Player Controller | Targeting")
		bool bIsDoubleTapReady;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Player Controller | Targeting")
		FTimerHandle DoubleTapTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Player Controller | Targeting")
		TArray<FOnScreenTargetInfo> TargetableActorsInfo;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Player Controller | Input | ")
		float TurnRateGamepad = 75.0f;

	/// <summary>
	/// Will try to save the game, a new save game object will be created if one doesn't already exist.
	/// </summary>
	/// <param name="InSaveSlotName">Name of the slot to save the game in</param>
	/// <param name="InUserIndex">The user index of the player that is saving</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Save Data")
		void RequestSaveGame(FString InSaveSlotName, int InUserIndex);

	/// <summary>
	/// Will try to load the game if a save slot exists
	/// </summary>
	/// <param name="InSaveSlotName">Name of the save slot we want to load from</param>
	/// <param name="InUserIndex">The user index of the player that the save slot belongs to</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Save Data")
		void RequestLoadSave(FString InSaveSlotName, int InUserIndex);

	//Calls SelectNextSlot from the player's spell selection bar widget
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | UI | Spell Selection Bar")
		void RequestSelectNextSpell();

	//Calls SelectPreviousSlot from the player's spell selection bar widget
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | UI | Spell Selection Bar")
		void RequestSelectPreviousSpell();

	//Calls ExecutePrimaryAction from SigilCharacter
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | ")
		void RequestExecutePrimaryAction();

	//Calls ExecuteSecondaryAction from SigilCharacter
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | ")
		void RequestExecuteSecondaryAction();

	//Calls Jump from SigilCharacter
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | ")
		void RequestJump();

	//Calls StopJumping from SigilCharacter
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | ")
		void RequestStopJumping();

	//Calls AddControllerYawInput and AddControllerPitchInput from Pawn to rotate the player's camera 
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | ")
		void RequestLook2D(FVector2D InLook2D);

	//Calls AddMovementInput from Pawn to move the player character
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | Input | ")
		void RequestMove2D(FVector2D InMove2D);

	//Calls TargetTrace from SigilCharacter and passes the TargetComponent output to the TargetLock widget
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void FindTarget();

	/// <summary>
	/// Calls SelectSpecificSlot from the SpellSelectionBar widget
	/// </summary>
	/// <param name="SlotNumber">The number of the slot the player wants to select</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void RequestSelectSpecificSlot(int SlotNumber);

	//Calls RemoveTarget from SigilCharacter, hides the TargetLock widget and sets its TargetComponentRef to nullptr
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void RequestReleaseTarget();

	//Calls ReleaseWidget from the Spellbook widget
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void RequestReleaseWidget();

	//Checks if the player double tapped the TargetLock_Tap input. 5.0 Enhanced Input does not have a double tap trigger.
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void CheckForDoubleTap();

	//Sets bIsDoubleTapReady to false and calls FindTarget
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void ExecuteTargetLockSingleTap();

	//Gets all actors that are in the player screen that implement USigilTargetingInterface and adds them to the TargetableActorsInfo array
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void GetAllTargetableActorsOnScreen();

	/// <summary>
	/// Checks if the X and Y values of InVector2D are is within the bounds of the viewport
	/// </summary>
	/// <param name="InVector2D">The 2D vector that the function will check</param>
	/// <returns>Returns true if InVector2D is in the viewport</returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		bool ValidateScreenPosition(FVector2D InVector2D);

	/*UFUNCTION(VisibleAnywhere, Category = "Sigil Player Controller | ")
		void FlickToNewTargetOnScreen();*/

	/// <summary>
	/// Will set NewTargetActor as the player's target if certain conditions are met
	/// </summary>
	/// <param name="NewTargetActor">The actor we want to set as the new target</param>
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void RequestSetNewTarget(AActor* NewTargetActor);

	//Tries to set the player's target to the actor from TargetableActorsInfo that is closest to the center of the player's screen
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void ChangeTargetByClosestToScreenCenter();

	//Calls ChangeTargetByClosestToScreenCenter if the player has a target selected and bIsCameraLocked is true
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void AttemptTargetSwap();


public:
	// Called every frame
	virtual void PlayerTick(float DeltaTime);

	//Will show or hide the mouse cursor depending on the value of bShowCursor
	UFUNCTION(BlueprintCallable)
		void SetPlayerMouseCursorVisibility(bool bShowCursor);

	//Calls RefreshWidgetSlots from the SpellSelectionBar widget
	UFUNCTION(BlueprintCallable, Category = "Sigil Player Controller | ")
		void RequestRefreshSpellBar();

	//Getter for SaveSlotName
	UFUNCTION(BlueprintCallable)
		FString GetSaveSlotName() { return SaveSlotName; }

#pragma region INPUT
	protected:

		//Input actions
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_Jump;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_Look2D;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_Look2DGamepad;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_Menu;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_Move2D;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_PrimaryAction;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SecondaryAction;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectNextSpell;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectPreviousSpell;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot1;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot2;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot3;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot4;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot5;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot6;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot7;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot8;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_SelectSlot9;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_TargetLock_DoubleTap;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_TargetLock_Hold;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_TargetLock_Tap;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Actions")
			UInputAction* IA_ToggleMouseCursor;

		bool bToggleMouseFlipFlop = true;

		//Input mappings
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Mappings")
			UInputMappingContext* BaseMappingContext;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sigil Player Controller | Input | Mappings")
			int32 BaseMappingPriority = 0;

		//Input functions
		void InF_Jump(const FInputActionValue& Value);
		void InF_Look2D(const FInputActionValue& Value);
		void InF_Look2DGamepad(const FInputActionValue& Value);
		void InF_Menu(const FInputActionValue& Value);
		void InF_Move2D(const FInputActionValue& Value);
		void InF_PrimaryAction(const FInputActionValue& Value);
		void InF_SecondaryAction(const FInputActionValue& Value);
		void InF_SelectNextSpell(const FInputActionValue& Value);
		void InF_SelectPreviousSpell(const FInputActionValue& Value);
		void InF_SelectSlot1(const FInputActionValue& Value);
		void InF_SelectSlot2(const FInputActionValue& Value);
		void InF_SelectSlot3(const FInputActionValue& Value);
		void InF_SelectSlot4(const FInputActionValue& Value);
		void InF_SelectSlot5(const FInputActionValue& Value);
		void InF_SelectSlot6(const FInputActionValue& Value);
		void InF_SelectSlot7(const FInputActionValue& Value);
		void InF_SelectSlot8(const FInputActionValue& Value);
		void InF_SelectSlot9(const FInputActionValue& Value);
		void InF_TargetLock_DoubleTap(const FInputActionValue& Value);
		void InF_TargetLock_Hold(const FInputActionValue& Value);
		void InF_TargetLock_Tap(const FInputActionValue& Value);
		void InF_ToggleMouseCursor(const FInputActionValue& Value);

#pragma endregion

};
