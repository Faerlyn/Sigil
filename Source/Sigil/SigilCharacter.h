

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterAttributesComponent.h"
#include "SpellcastingComponent.h"
#include "SigilCharacter.generated.h"

UCLASS()
class SIGIL_API ASigilCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASigilCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterAttributesComponent* CharacterAttributesComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpellcastingComponent* SpellcastingComponent;

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AddSpellToSpellbook(UDA_SpellInfo* InSpellInfo);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		bool RemoveSpellFromSpellbook(UDA_SpellInfo* InSpellInfo);*/

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetSelectedSpellIndex(int NewIndex);*/
};
