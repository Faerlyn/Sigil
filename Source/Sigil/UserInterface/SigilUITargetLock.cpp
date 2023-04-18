


#include "SigilUITargetLock.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void USigilUITargetLock::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void USigilUITargetLock::NativeConstruct()
{
	Super::NativeConstruct();

	RotateWidget();

}

void USigilUITargetLock::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void USigilUITargetLock::SetbIsHidden(bool InBool)
{
	//If bIsHidden is not equal to InBool
	if (bIsHidden != InBool)
	{
		//Set bIsHidden to InBool
		bIsHidden = InBool;
	}
}

void USigilUITargetLock::SetbIsWidgetLocked(bool InBool)
{
	//If bIsWidgetLocked is not equal to InBool
	if (bIsWidgetLocked != InBool)
	{
		//Set bIsWidgetLocked to InBool
		bIsWidgetLocked = InBool;
	}
}

UPrimitiveComponent* USigilUITargetLock::GetTargetComponentRef()
{
	//Validate TargetComponentRef
	if (TargetComponentRef)
	{
		//Return TargetComponentRef
		return TargetComponentRef;
	}

	return nullptr;
}

void USigilUITargetLock::HideWidget()
{
	//If the widget is not hidden
	if (!bIsHidden)
	{
		//Play Anim_FadeIn in reverse
		PlayAnimation(Anim_FadeIn, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);

		//Set bIsHidden to true
		SetbIsHidden(true);
	}
}

void USigilUITargetLock::ShowWidget()
{
	//If the widget is hidden
	if (bIsHidden)
	{
		//Set the widget's postion on the screen
		SetWidgetPosition();

		//Play Anim_FadeIn
		PlayAnimation(Anim_FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);

		//Set bIsHidden to false
		SetbIsHidden(false);
	}
}

void USigilUITargetLock::SetWidgetPosition()
{
	//If the widget is locked on
	if (bIsWidgetLocked)
	{
		//Set the widget's position to TargetWidgetPosition
		UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(TargetWidgetPosition);
	}
	//If the widget's current position is within 5 of TargetWidgetPosition
	else if (UKismetMathLibrary::EqualEqual_Vector2DVector2D(CurrentWidgetPosition, TargetWidgetPosition, 5.0f))
	{
		//Set bIsWidgetLocked to true
		SetbIsWidgetLocked(true);

		//Set the widget's position to TargetWidgetPosition
		UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(TargetWidgetPosition);
	}
	//Otherwise, move the widget towards its target
	else
	{	
		float DeltaSeconds = GetWorld()->GetDeltaSeconds();

		//Interp the widget's current position to TargetWidgetPosition
		FVector2D InterpVector = UKismetMathLibrary::Vector2DInterpTo(CurrentWidgetPosition, TargetWidgetPosition, DeltaSeconds, WidgetInterpSpeed);

		//Set the widget's position to InterpVector
		UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(InterpVector);
	}
}

void USigilUITargetLock::SetWidgetTargetPosition()
{
	//Validate TargetComponentRef
	if (TargetComponentRef)
	{
		//Set TargetWidgetPosition to where TargetComponentRef is on the player's screen
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), TargetComponentRef->GetComponentLocation(), TargetWidgetPosition, true);
	}
}

void USigilUITargetLock::GetWidgetCurrentPosition()
{
	//Set CurrentWidgetPosition to the widget's current position
	CurrentWidgetPosition = UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->GetPosition();
}

void USigilUITargetLock::UpdateWidgetPosition()
{
	//Get the widget's current position
	GetWidgetCurrentPosition();

	//Set the widget's target position
	SetWidgetTargetPosition();

	//Move the widget towards its target position
	SetWidgetPosition();
}

void USigilUITargetLock::SetNewTargetComponentRef(UPrimitiveComponent* NewTargetComponentRef)
{
	//Validate NewTargetComponentRef
	if (NewTargetComponentRef)
	{
		//If TargetComponentRef is not equal to NewTargetComponentRef
		if (TargetComponentRef != NewTargetComponentRef)
		{
			//Set TargetComponentRef to NewTargetComponentRef
			TargetComponentRef = NewTargetComponentRef;

			//Show the widget
			ShowWidget();

			//Set bIsWidgetLocked to false
			SetbIsWidgetLocked(false);

			//Play the target lock sound effect
			UGameplayStatics::PlaySound2D(this, TargetLockSFX, 1.0f, 1.0f, 0.0f, nullptr, GetOwningPlayer(), true);
		}
	}
	else
	{
		//Unselect the target and hide the widget
		ClearTarget();
	}
}

void USigilUITargetLock::RotateWidget()
{
	//Play AnimRotate on loop
	PlayAnimation(Anim_Rotate, 0.0f, 0, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void USigilUITargetLock::ClearTarget()
{
	//Set TargetComponentRef to nullptr;
	TargetComponentRef = nullptr;

	//Hide the widget
	HideWidget();
}

void USigilUITargetLock::UpdateWidget()
{
	//Update the widget's position
	UpdateWidgetPosition();
}
