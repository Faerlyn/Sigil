

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interface/SigilTargetingInterface.h"
#include "SigilCharacter.generated.h"

class UArrowComponent;
class UCameraComponent;
class USpringArmComponent;

class AMagicShieldActor;
class ASpellProjectileActor;
class UCharacterAttributesComponent;
class USigilDamageHandlerComponent;
class USpellcastingComponent;

UCLASS()
class SIGIL_API ASigilCharacter : public ACharacter, public ISigilTargetingInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//SigilTargetingInterface implementation
	void GetActorTargetInfo_Implementation(AActor*& NewTarget, FName& NewTargetName, FText& NewTargetMessage) override;
	UPrimitiveComponent* GetTargetComponent_Implementation() override;

	// Called when the character takes any damage
	UFUNCTION()
		void SigilReceiveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Input")
		float TurnRateGamepad = 50.0f;

	USigilDamageHandlerComponent* DamageHandlerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCharacterAttributesComponent* CharacterAttributesComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpellcastingComponent* SpellcastingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sigil Character | Reference")
		TSubclassOf<ASpellProjectileActor> SpellProjectileBP;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Camera")
		USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Components")
		UArrowComponent* TargetArrow;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Components")
		USpringArmComponent* ShieldArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Character | Components")
		UArrowComponent* ShieldArrow;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Components")
		USpringArmComponent* ProjectileArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sigil Character | Components")
		UArrowComponent* ProjectileArrow;

	UPROPERTY(EditAnywhere, Category = "Sigil Character | Reference")
		TSubclassOf<AMagicShieldActor> MagicShieldBP;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Reference")
		AMagicShieldActor* MagicShieldRef;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Reference")
		AActor* CurrentTargetRef;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Reference")
		UPrimitiveComponent* CurrentTargetComponentRef;

	UPROPERTY(VisibleAnywhere, Category = "Sigil Character | Targeting System")
		bool bIsCameraLocked = true;

	UPROPERTY(EditAnywhere, Category = "Sigil Character | Targeting System")
		float TraceLength = 1000.0f;

	// Makes the camera look at the current target's location by interping the controller's rotation
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		void LockCameraToTarget();

	//UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
	//	void DisengageCameraLockOn();

	
	//Setter for bIsCameraLocked
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		void SetCameraLockOn(bool InBool);	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Getter for CharacterAttributesComponent
	UFUNCTION()
		UCharacterAttributesComponent* GetCharacterAttributesComponent() { return CharacterAttributesComponent; }
	
	//Getter for SpellcastingComponent
	UFUNCTION()
		USpellcastingComponent* GetSpellcastingComponent() { return SpellcastingComponent; }

	//Returns the currently targeted actor
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Player Input")
		AActor* GetCurrentTargetRef();

	// Called when the character health points reach zero
	UFUNCTION()
		void OnDeath();

	//Executes the character's current primary action. Only casts the equipped spell for now.
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Player Input")
		void ExecutePrimaryAction();

	//Executes the character's current secondary action. Only activates/deactivates the magic for now.
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Player Input")
		void ExecuteSecondaryAction();

	/// <summary>
	/// Executes a sphere trace to find a targetable actor, the length of the trace is dependent on the value of SigilCharacter's TraceLength variable.
	/// </summary>
	/// <param name="NewTargetComponent">Outputs the component that blocks the trace</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System | Trace")
		bool TargetTrace(UPrimitiveComponent*& NewTargetComponent);

	//Toggles bIsCameraLocked between true and false
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		void ToggleCameraLockOn();

	//Getter for bIsCameraLocked
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		bool GetIsCameraLocked() { return bIsCameraLocked; }

	/// <summary>
	/// Checks if NewTargetActor implements USigilTargetingInterface and sets CurrentTargetComponentRef to this actor's TargetComponent.
	/// Will return nullptr if one doesn't exist or the actor does not implement the interface.
	/// </summary>
	/// <param name="NewTargetActor">Actor that is checked for USigilTargetingInterface</param>
	/// <param name="NewTargetComponent">NewTargetActor's TargetComponent</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		bool SetNewTarget(AActor* NewTargetActor, UPrimitiveComponent*& NewTargetComponent);

	//Sets CurrentTargetRef and CurrentTargetComponentRef to nullptr
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		void RemoveTarget();

	//Returns true if CurrentTargetRef is valid
	UFUNCTION(BlueprintCallable, Category = "Sigil Character | Targeting System")
		bool HasValidTarget();
	
};
