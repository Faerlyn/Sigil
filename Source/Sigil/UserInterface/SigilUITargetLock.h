

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilUITargetLock.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilUITargetLock : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient, Category = "Target Lock | Animations")
		UWidgetAnimation* Anim_FadeIn = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidgetAnim), Transient, Category = "Target Lock | Animations")
		UWidgetAnimation* Anim_Rotate = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target Lock | References")
		UPrimitiveComponent* TargetComponentRef;

	UPROPERTY(EditAnywhere, Category = "Target Lock | SFX")
		USoundBase* TargetLockSFX;

	//Stores the widget's current position on the viewport
	FVector2D CurrentWidgetPosition;

	//Stores the position on the viewport where we want the widget to be
	FVector2D TargetWidgetPosition;

	//Determines how quickly the widget will interp towards its target position
	UPROPERTY(EditAnywhere, Category = "Target Lock | Settings")
		float WidgetInterpSpeed = 10;

	//Is the widget hidden?
	UPROPERTY(VisibleAnywhere, Category = "Target Lock | Settings")
		bool bIsHidden;

	//Is the widget locked to its target position?
	UPROPERTY(VisibleAnywhere, Category = "Target Lock | Settings")
		bool bIsWidgetLocked;

	//Setter for bIsHidden
	void SetbIsHidden(bool InBool);

	//Setter for bIsWidgetLocked
	void SetbIsWidgetLocked(bool InBool);

	//Sets the widget's position to its target positon if bIsWidgetLocked is true.
	//Otherwise, interp the widget towards its target position.
	UFUNCTION()
		void SetWidgetPosition();

	//Sets the widget's target position by getting the target's position on the viewport
	UFUNCTION()
		void SetWidgetTargetPosition();

	//Gets the widget's current position on the viewport
	UFUNCTION()
		void GetWidgetCurrentPosition();

	//Updates the widget's position on the viewport
	UFUNCTION()
		void UpdateWidgetPosition();

	//Plays the AnimRotate animation on loop
	UFUNCTION()
		void RotateWidget();
	
public:

	//Getter for TargetComponentRef
	UFUNCTION(BlueprintCallable)
		UPrimitiveComponent* GetTargetComponentRef();

	//Setter for TargetComponentRef
	UFUNCTION(BlueprintCallable)
		void SetNewTargetComponentRef(UPrimitiveComponent* NewTargetComponentRef);

	//Unselects the current target and hides the widget
	UFUNCTION(BlueprintCallable)
		void ClearTarget();

	//Hides the widget
	UFUNCTION(BlueprintCallable)
		void HideWidget();

	//Shows the widget
	UFUNCTION(BlueprintCallable)
		void ShowWidget();

	//Should be called when this widget needs to be updated.
	//Currently only updates the widget's position.
	UFUNCTION(BlueprintCallable)
		void UpdateWidget();
};
