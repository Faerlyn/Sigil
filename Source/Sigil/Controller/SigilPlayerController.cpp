


#include "SigilPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "../Actor/Character/SigilCharacter.h"
#include "../Actor/Component/SpellbookComponent.h"
#include "../Actor/Component/SpellcastingComponent.h"
#include "../DataAsset/UDA_SpellInfo.h"
#include "../SaveGame/SigilSaveGame.h"
#include "../UserInterface/SigilMenuSelectionBar.h"
#include "../UserInterface/SigilMenuSpellbook.h"
#include "../UserInterface/SigilUIPlayerHUD.h"
#include "../UserInterface/SigilUITargetLock.h"
#include "../UserInterface/SigilWindowFrame.h"

void ASigilPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Create the PlayerHUD widget
	PlayerHUDWidget = Cast<USigilUIPlayerHUD>(CreateWidget(this, PlayerHUDWidgetBP));

	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToPlayerScreen();

		TargetLockWidget = PlayerHUDWidget->GetTargetLockWidget();
	}

	//Create the Spellbook widget
	SpellbookWidget = Cast<USigilWindowFrame>(CreateWidget(this, WindowFrameWidgetBP));
	if (SpellbookWidget)
	{
		SpellbookWidget->SetWindowContent(SpellbookWidgetBP);
	}

	//Try to load a save
	RequestLoadSave(SaveSlotName, 0);

	//Add the Enhanced Input mapping context to the player
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (BaseMappingContext)
			{
				InputSystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
			}
		}
	}
}
	

void ASigilPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Bind player input
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_Jump)
		{
			PlayerEnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_Jump);
		}

		if (IA_Look2D)
		{
			PlayerEnhancedInputComponent->BindAction(IA_Look2D, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_Look2D);
		}

		if (IA_Look2DGamepad)
		{
			PlayerEnhancedInputComponent->BindAction(IA_Look2DGamepad, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_Look2DGamepad);
		}

		if (IA_Menu)
		{
			PlayerEnhancedInputComponent->BindAction(IA_Menu, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_Menu);
		}

		if (IA_Move2D)
		{
			PlayerEnhancedInputComponent->BindAction(IA_Move2D, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_Move2D);
		}

		if (IA_PrimaryAction)
		{
			PlayerEnhancedInputComponent->BindAction(IA_PrimaryAction, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_PrimaryAction);
		}

		if (IA_SecondaryAction)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SecondaryAction, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SecondaryAction);
		}

		if (IA_SelectNextSpell)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectNextSpell, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectNextSpell);
		}

		if (IA_SelectPreviousSpell)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectPreviousSpell, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectPreviousSpell);
		}

		if (IA_SelectSlot1)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot1, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot1);
		}

		if (IA_SelectSlot2)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot2, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot2);
		}

		if (IA_SelectSlot3)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot3, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot3);
		}

		if (IA_SelectSlot4)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot4, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot4);
		}

		if (IA_SelectSlot5)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot5, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot5);
		}

		if (IA_SelectSlot6)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot6, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot6);
		}

		if (IA_SelectSlot7)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot7, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot7);
		}

		if (IA_SelectSlot8)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot8, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot8);
		}

		if (IA_SelectSlot9)
		{
			PlayerEnhancedInputComponent->BindAction(IA_SelectSlot9, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_SelectSlot9);
		}

		if (IA_TargetLock_DoubleTap)
		{
			PlayerEnhancedInputComponent->BindAction(IA_TargetLock_DoubleTap, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_TargetLock_DoubleTap);
		}

		if (IA_TargetLock_Hold)
		{
			PlayerEnhancedInputComponent->BindAction(IA_TargetLock_Hold, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_TargetLock_Hold);
		}

		if (IA_TargetLock_Tap)
		{
			PlayerEnhancedInputComponent->BindAction(IA_TargetLock_Tap, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_TargetLock_Tap);
		}

		if (IA_ToggleMouseCursor)
		{
			PlayerEnhancedInputComponent->BindAction(IA_ToggleMouseCursor, ETriggerEvent::Triggered, this, &ASigilPlayerController::InF_ToggleMouseCursor);
		}
	}

	if (InputComponent)
	{
		InputComponent.Get()->BindKey(EKeys::LeftMouseButton, EInputEvent::IE_Released, this, &ASigilPlayerController::RequestReleaseWidget);
	}


}

void ASigilPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		//If the player camera is locked and the player has a valid target
		if (SC->GetIsCameraLocked() && SC->HasValidTarget())
		{
			//Call GetAllTargetableActorsOnScreen
			GetAllTargetableActorsOnScreen();			
		}
	}
}

void ASigilPlayerController::SetPlayerMouseCursorVisibility(bool bShowCursor)
{
	if (bShowCursor)
	{
		//Stop the camera from moving when the mouse is moved
		SetIgnoreLookInput(false);

		//Set input mode to game and UI
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(nullptr);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(true);

		SetInputMode(InputMode);

		//Show the mouse cursor
		bShowMouseCursor = true;
	}
	else
	{
		ResetIgnoreLookInput();

		//Set input mode to game only
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		//Hide the mouse cursor
		bShowMouseCursor = false;
	}
}



void ASigilPlayerController::RequestSaveGame(FString InSaveSlotName, int InUserIndex)
{
	//If a save game exists for this save slot and user index
	if (UGameplayStatics::DoesSaveGameExist(InSaveSlotName, 0))
	{
		//Load the save game and store a reference to it
		SaveGameRef = Cast<USigilSaveGame>(UGameplayStatics::LoadGameFromSlot(InSaveSlotName, InUserIndex));
	}
	else
	{
		//Create a new save game and store a reference to it
		SaveGameRef = Cast<USigilSaveGame>(UGameplayStatics::CreateSaveGameObject(USigilSaveGame::StaticClass()));
	}

	//If SaveGameRef is valid
	if (SaveGameRef)
	{
		//Cast the pawn to SigilCharacter and validate it
		if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
		{
			//Call SaveGame from USigilSaveGame to save player information
			SaveGameRef->SaveGame(InSaveSlotName, InUserIndex, PlayerName, SC->GetActorTransform(), GetControlRotation(), SC->GetSpellcastingComponent()->GetSpellbookComponent()->GetPlayerSpells(), SC->GetSpellcastingComponent()->GetPreparedSpells());

			//Try to save the game and if it is saved successfully
			if (UGameplayStatics::SaveGameToSlot(SaveGameRef, InSaveSlotName, InUserIndex))
			{
				//Print a message to the log to say that the game was saved
				UE_LOG(LogTemp, Display, TEXT("Success: Game saved"));
				//UKismetSystemLibrary::PrintString(this, "Game saved!", true, true, FLinearColor::Yellow, 2.0f, "GameSave");
			}
			else
			{
				//Print a message to the log warning that the game was not saved
				UE_LOG(LogTemp, Warning, TEXT("Error: Game was not saved"));
				//UKismetSystemLibrary::PrintString(this, "Game not saved!", true, true, FLinearColor::Yellow, 2.0f, "GameSave");
			}
		}
	}
}

void ASigilPlayerController::RequestLoadSave(FString InSaveSlotName, int InUserIndex)
{
	//Check that a save game exists for the provided slot name and user index
	if (UGameplayStatics::DoesSaveGameExist(InSaveSlotName, InUserIndex))
	{
		//Print a message to the log saying a save game was found
		UE_LOG(LogTemp, Display, TEXT("Success: Save game was found"));

		//Load the save game and store a reference to it
		SaveGameRef = Cast<USigilSaveGame>(UGameplayStatics::LoadGameFromSlot(InSaveSlotName, InUserIndex));

		//Validate SaveGameRef
		if (SaveGameRef)
		{
			//Cast the pawn to SigilCharacter
			if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
			{
				FTransform PlayerCharacterTransform;
				FRotator PlayerControllerRotation;
				TArray<UDA_SpellInfo*> NewPlayerSpells;
				TArray<UDA_SpellInfo*> NewPreparedSpells;

				//Call LoadGame from USigilSaveGame to load the information stored by SaveGame
				SaveGameRef->LoadGame(PlayerName, PlayerCharacterTransform, PlayerControllerRotation, NewPlayerSpells, NewPreparedSpells);

				//Set the player character's transform
				SC->SetActorTransform(PlayerCharacterTransform, false, false);

				//Set the controller's rotation
				SetControlRotation(PlayerControllerRotation);

				//Load any player created spells and store them in the PlayerSpells array
				SC->GetSpellcastingComponent()->GetSpellbookComponent()->SetPlayerSpells(NewPlayerSpells);

				//Set the player's prepared spells from when they saved the game
				SC->GetSpellcastingComponent()->SetPreparedSpells(NewPreparedSpells);

				//Print a message to the console saying that the save game was loaded
				UE_LOG(LogTemp, Display, TEXT("Success: Save game loaded"));
				//UKismetSystemLibrary::PrintString(this, "Game loaded!", true, true, FLinearColor::Yellow, 2.0f, "GameSave");

				//Refresh the player's spell selection bar
				PlayerHUDWidget->GetSpellSelectionBarWidget()->RefreshWidgetSlots();
			}
		}
		else
		{
			//Print a message to the log warning that the save game was not loaded
			UE_LOG(LogTemp, Warning, TEXT("Error: Save game was not loaded"));
			//UKismetSystemLibrary::PrintString(this, "Game not loaded!", true, true, FLinearColor::Yellow, 2.0f, "GameSave");
		}
	}
	else
	{
		//Print a message to the log saying that no save game exists
		UE_LOG(LogTemp, Warning, TEXT("Warning: No save game exists for this slot name and user index"));
	}
}

void ASigilPlayerController::RequestSelectNextSpell()
{
	PlayerHUDWidget->GetSpellSelectionBarWidget()->SelectNextSlot();
}

void ASigilPlayerController::RequestSelectPreviousSpell()
{
	PlayerHUDWidget->GetSpellSelectionBarWidget()->SelectPreviousSlot();
}

void ASigilPlayerController::RequestExecutePrimaryAction()
{
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		SC->ExecutePrimaryAction();
	}
}

void ASigilPlayerController::RequestExecuteSecondaryAction()
{
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		SC->ExecuteSecondaryAction();
	}
}

void ASigilPlayerController::RequestJump()
{
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		SC->Jump();
	}
}

void ASigilPlayerController::RequestStopJumping()
{
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		SC->StopJumping();
	}
}

void ASigilPlayerController::RequestLook2D(FVector2D InLook2D)
{
	if (GetPawn())
	{
		GetPawn()->AddControllerYawInput(InLook2D.X);
		GetPawn()->AddControllerPitchInput(InLook2D.Y);

		AttemptTargetSwap();
	}
}

void ASigilPlayerController::RequestMove2D(FVector2D InMove2D)
{
	if (GetPawn())
	{
		FRotator PlayerControlRotation = GetControlRotation();
		PlayerControlRotation.Pitch = 0.0f;

		FVector PlayerRightVector = UKismetMathLibrary::GetRightVector(PlayerControlRotation);

		GetPawn()->AddMovementInput(PlayerRightVector, InMove2D.X, false);

		PlayerControlRotation.Roll = 0.0f;

		FVector PlayerForwardVector = UKismetMathLibrary::GetForwardVector(PlayerControlRotation);

		GetPawn()->AddMovementInput(PlayerForwardVector, InMove2D.Y, false);
	}
}

void ASigilPlayerController::FindTarget()
{
	//Cast the pawn to SigilCharacter and validate it
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		UPrimitiveComponent* NewTargetComponent;

		//Call TargetTrace from SigilCharacter
		if (SC->TargetTrace(NewTargetComponent))
		{
			//Get the TargetComponent reference from the player HUD widget and validate it
			if (UPrimitiveComponent* CurrentTargetComponent = PlayerHUDWidget->GetTargetLockWidget()->GetTargetComponentRef())
			{
				//If NewTargetComponent is not equal to CurrentTargetComponent
				if (NewTargetComponent != CurrentTargetComponent)
				{
					//Set PlayerHUDWidget's TargetComponentRef to NewTargetComponent
					PlayerHUDWidget->GetTargetLockWidget()->SetNewTargetComponentRef(NewTargetComponent);
				}
			}
			else
			{
				//Set PlayerHUDWidget's TargetComponentRef to NewTargetComponent
				PlayerHUDWidget->GetTargetLockWidget()->SetNewTargetComponentRef(NewTargetComponent);
			}
		}
	}
}

void ASigilPlayerController::RequestSelectSpecificSlot(int SlotNumber)
{
	PlayerHUDWidget->GetSpellSelectionBarWidget()->SelectSpecificSlot(SlotNumber - 1);
}

void ASigilPlayerController::RequestRefreshSpellBar()
{
	PlayerHUDWidget->GetSpellSelectionBarWidget()->RefreshWidgetSlots();
}

void ASigilPlayerController::RequestReleaseTarget()
{
	//Cast the pawn to SigilCharacter and validate it
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		//Validate TargetLockWidget
		if (TargetLockWidget)
		{
			//Call RemoveTarget from SigilCharacter
			SC->RemoveTarget();

			//Hide TargetLockWidget
			TargetLockWidget->HideWidget();

			//Set TargetLockWidget's TargetComponentRef to nullptr
			TargetLockWidget->SetNewTargetComponentRef(nullptr);
		}
	}
}

void ASigilPlayerController::RequestReleaseWidget()
{
	if (SpellbookWidget)
	{
		FPointerEvent MouseEvent;

		SpellbookWidget->ReleaseWidget(MouseEvent);
	}
}

void ASigilPlayerController::CheckForDoubleTap()
{
	//If bIsDoubleTapReady is false
	if (!bIsDoubleTapReady)
	{
		//Start a timer, pressing the TargetLock_Tap key while this timer is running will register the double tap
		GetWorld()->GetTimerManager().SetTimer(DoubleTapTimerHandle, this, &ASigilPlayerController::ExecuteTargetLockSingleTap, 0.2f, false);

		//Set bIsDoubleTapReady to true
		bIsDoubleTapReady = true;
	}
	else
	{
		//Cancel the double tap timer
		GetWorld()->GetTimerManager().ClearTimer(DoubleTapTimerHandle);

		//Call RequestReleaseTarget
		RequestReleaseTarget();

		//Set bIsDoubleTapReady to false
		bIsDoubleTapReady = false;
	}
}

void ASigilPlayerController::ExecuteTargetLockSingleTap()
{
	//Set bIsDoubleTapReady to false
	bIsDoubleTapReady = false;

	//Call FindTarget
	FindTarget();
}

void ASigilPlayerController::GetAllTargetableActorsOnScreen()
{
	//Empty TargetableActorsInfo
	TargetableActorsInfo.Empty();

	TArray<AActor*> OutActors;

	//Get all actors in the current world that implement USigilTargetingInterface
	UGameplayStatics::GetAllActorsWithInterface(this, USigilTargetingInterface::StaticClass(), OutActors);

	//Iterate through OutActors
	for (size_t i = 0; i < OutActors.Num(); i++)
	{
		//Check that the actor is not the player's pawn
		if (OutActors[i] != GetPawn())
		{
			//Check that the actor is being rendered
			if (OutActors[i]->WasRecentlyRendered(0.1f))
			{
				AActor* NewTarget;
				FName NewTargetName;
				FText NewTargetMessage;

				//Get the actor's target information
				ISigilTargetingInterface::Execute_GetActorTargetInfo(OutActors[i], NewTarget, NewTargetName, NewTargetMessage);

				//Validate NewTarget
				if (NewTarget)
				{
					FVector2D NewTargetScreenLocation;

					//Get NewTarget's position on the screen
					if (ProjectWorldLocationToScreen(NewTarget->GetActorLocation(), NewTargetScreenLocation, true))
					{
						//Check that the actor is not off screen
						if (ValidateScreenPosition(NewTargetScreenLocation))
						{
							FOnScreenTargetInfo NewTargetInfo;
							NewTargetInfo.TargetActor = NewTarget;
							NewTargetInfo.ActorName = NewTargetName;

							//Get the viewport's sizr
							FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

							//Get the location of the center of the screen
							FVector2D ViewportCenter = ViewportSize / 2;

							//Get the actor's screen position relative to the center of the screen
							FVector2D TargetLocationFromScreenCenter = NewTargetScreenLocation - ViewportCenter;

							//Get NewTarget's distance to the center of the screen using Pythagoras' Theorem
							NewTargetInfo.DistanceToScreenCenter = UKismetMathLibrary::Sqrt(UKismetMathLibrary::Square(TargetLocationFromScreenCenter.X) + UKismetMathLibrary::Square(TargetLocationFromScreenCenter.Y));

							//Add the actor to TargetableActorsInfo
							TargetableActorsInfo.Add(NewTargetInfo);

							/*FString MessageString;

							MessageString.Append(UKismetStringLibrary::Conv_NameToString(NewTargetInfo.ActorName));
							MessageString.Append("- X: ");
							MessageString.Append(UKismetStringLibrary::Conv_FloatToString(TargetLocationFromScreenCenter.X));
							MessageString.Append(" Y: ");
							MessageString.Append(UKismetStringLibrary::Conv_FloatToString(TargetLocationFromScreenCenter.Y));

							UKismetSystemLibrary::PrintString(this, MessageString, true, true, FLinearColor::Yellow, 2.0f, NewTargetInfo.ActorName);*/
						}
					}
				}
			}
		}
	}
}

bool ASigilPlayerController::ValidateScreenPosition(FVector2D InVector2D)
{
	//Get the viewport's size
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

	//InVector2D is inside the viewport if its X and Y values are greater than or equal to 0 and less than or equal to the ViewportSize's X and Y values.
	if (InVector2D.X >= 0.0f && InVector2D.Y >= 0.0f && InVector2D.X <= ViewportSize.X && InVector2D.Y <= ViewportSize.Y)
	{
		//InVector2D is inside the viewport
		return true;
	}
	else
	{
		//InVector2D is off screen (not in the viewport)
		return false;
	}
}

void ASigilPlayerController::RequestSetNewTarget(AActor* NewTargetActor)
{
	//If the distance between the player character and the new target actor is less than 1000.0f
	if (UKismetMathLibrary::Vector_Distance(NewTargetActor->GetActorLocation(), GetPawn()->GetActorLocation()) < 1000.0f)
	{
		//Cast the pawn to SigilCharacter and validate it
		if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
		{
			//If the current target actor is not the same as the new target actor
			if (SC->GetCurrentTargetRef() != NewTargetActor)
			{
				UPrimitiveComponent* NewTargetComponent;

				//Set new target actor as the new target
				if (SC->SetNewTarget(NewTargetActor, NewTargetComponent))
				{
					//If the current target component is not the same as the new target component
					if (PlayerHUDWidget->GetTargetLockWidget()->GetTargetComponentRef() != NewTargetComponent)
					{
						//Set TargetLockWidget's target component ref to NewTargetComponent
						PlayerHUDWidget->GetTargetLockWidget()->SetNewTargetComponentRef(NewTargetComponent);
					}
					else
					{
						//Call ClearTarget from TargetLockWidget
						PlayerHUDWidget->GetTargetLockWidget()->ClearTarget();
					}

				}
			}
		}
	}

}

void ASigilPlayerController::ChangeTargetByClosestToScreenCenter()
{
	//If TargetableActorsInfo is not empty
	if (!TargetableActorsInfo.IsEmpty())
	{
		//Set ClosestTarget to the first element of TargetableActorsInfo
		FOnScreenTargetInfo ClosestTarget = TargetableActorsInfo[0];

		//Iterate through TargetableActorsInfo
		for (size_t i = 0; i < TargetableActorsInfo.Num(); i++)
		{
			//If the current element;s DistanceToScreenCenter is less than ClosestTarget's DistanceToScreenCenter
			if (TargetableActorsInfo[i].DistanceToScreenCenter < ClosestTarget.DistanceToScreenCenter)
			{
				//Set ClosestTarget to the current element
				ClosestTarget = TargetableActorsInfo[i];
			}
		}

		//Try to set ClosestTarget as the new target
		RequestSetNewTarget(ClosestTarget.TargetActor);
	}
}

void ASigilPlayerController::AttemptTargetSwap()
{
	//Cast the pawn to SigilCharacter and validate it
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		//If the player has a valid target and the camera is locked
		if (SC->HasValidTarget() && SC->GetIsCameraLocked())
		{
			//Call ChangeTargetByClosestToScreenCenter
			ChangeTargetByClosestToScreenCenter();
		}
	}
}

void ASigilPlayerController::InF_Jump(const FInputActionValue& Value)
{
	//If jump key is being pressed
	if (Value.IsNonZero())
	{
		//Call RequestJump
		RequestJump();
	}
	else
	{
		//Call RequestStopJumping when the jump key is released
		RequestStopJumping();
	}
}

void ASigilPlayerController::InF_Look2D(const FInputActionValue& Value)
{
	RequestLook2D(FVector2D(Value[0], Value[1]));
}

void ASigilPlayerController::InF_Look2DGamepad(const FInputActionValue& Value)
{
	RequestLook2D(FVector2D((Value[0] * TurnRateGamepad * GetWorld()->GetDeltaSeconds()),
									(Value[1] * TurnRateGamepad * GetWorld()->GetDeltaSeconds())));
}

void ASigilPlayerController::InF_Menu(const FInputActionValue& Value)
{
	//Validate SpellbookWidget
	if (SpellbookWidget)
	{
		//Make the mouse cursor visible if the SpellbookWidget is in the viewport
		SetPlayerMouseCursorVisibility(SpellbookWidget->ToggleIsInViewPort());
	}
}

void ASigilPlayerController::InF_Move2D(const FInputActionValue& Value)
{
	RequestMove2D(FVector2D(Value[0], Value[1]));
}

void ASigilPlayerController::InF_PrimaryAction(const FInputActionValue& Value)
{
	RequestExecutePrimaryAction();
}

void ASigilPlayerController::InF_SecondaryAction(const FInputActionValue& Value)
{
	RequestExecuteSecondaryAction();
}

void ASigilPlayerController::InF_SelectNextSpell(const FInputActionValue& Value)
{
	RequestSelectNextSpell();
}

void ASigilPlayerController::InF_SelectPreviousSpell(const FInputActionValue& Value)
{
	RequestSelectPreviousSpell();
}

void ASigilPlayerController::InF_SelectSlot1(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(1);
}

void ASigilPlayerController::InF_SelectSlot2(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(2);
}

void ASigilPlayerController::InF_SelectSlot3(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(3);
}

void ASigilPlayerController::InF_SelectSlot4(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(4);
}

void ASigilPlayerController::InF_SelectSlot5(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(5);
}

void ASigilPlayerController::InF_SelectSlot6(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(6);
}

void ASigilPlayerController::InF_SelectSlot7(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(7);
}

void ASigilPlayerController::InF_SelectSlot8(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(8);
}

void ASigilPlayerController::InF_SelectSlot9(const FInputActionValue& Value)
{
	RequestSelectSpecificSlot(9);
}

void ASigilPlayerController::InF_TargetLock_DoubleTap(const FInputActionValue& Value)
{
}

void ASigilPlayerController::InF_TargetLock_Hold(const FInputActionValue& Value)
{
	//Cast the pawn to SigilCharacter and validate it
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetPawn()))
	{
		//If the player doesn't have a target
		if (!SC->HasValidTarget())
		{
			//Call FindTarget
			FindTarget();
		}

		//Call ToggleCameraLockOn from SigilCharacter
		SC->ToggleCameraLockOn();
	}
}

void ASigilPlayerController::InF_TargetLock_Tap(const FInputActionValue& Value)
{
	CheckForDoubleTap();
}

void ASigilPlayerController::InF_ToggleMouseCursor(const FInputActionValue& Value)
{
	//Call SetPlayerMouseCursorVisibility, pass bToggleMouseFlipFlop as the argument
	SetPlayerMouseCursorVisibility(bToggleMouseFlipFlop);

	//If bToggleMouseFlipFlop is true
	if (bToggleMouseFlipFlop)
	{
		//Set bToggleMouseFlipFlop to false
		bToggleMouseFlipFlop = false;
	}
	else
	{
		//Otherwise, set bToggleMouseFlipFlop to true
		bToggleMouseFlipFlop = true;
	}
}
