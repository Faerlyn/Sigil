

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellbookComponent.h"
#include "UDA_SpellInfo.h"
#include "SpellcastingComponent.generated.h"

USpellbookComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIGIL_API USpellcastingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellcastingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		USpellbookComponent* SpellbookComponent;

	UPROPERTY(VisibleAnywhere)
		TArray<UDA_SpellInfo*> PreparedSpells;

	UPROPERTY(VisibleAnywhere)
		UDA_SpellInfo* EquippedSpell;

	UPROPERTY(VisibleAnywhere)
		int SelectedSpellIndex = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		USpellbookComponent* GetSpellbookComponent() { return SpellbookComponent; }

	UFUNCTION(BlueprintCallable)
		TArray<UDA_SpellInfo*> GetPreparedSpells() { return PreparedSpells; }

	UFUNCTION(BlueprintCallable)
		void SetPreparedSpells(TArray<UDA_SpellInfo*> NewPreparedSpells) { PreparedSpells = NewPreparedSpells; }

	UFUNCTION(BlueprintCallable)
		UDA_SpellInfo* GetEquippedSpell() { return EquippedSpell; }

	UFUNCTION(BlueprintCallable)
		void EquipSelectedSpell();

	UFUNCTION(BlueprintCallable)
		int GetSelectedSpellIndex() { return SelectedSpellIndex; }

	UFUNCTION(BlueprintCallable)
		void SetSelectedSpellIndex(int NewIndex);

	UFUNCTION(BlueprintCallable)
		void AddNewPreparedSpell(UDA_SpellInfo* NewSpell);

	UFUNCTION(BlueprintCallable)
		void RemovePreparedSpell(UDA_SpellInfo* InSpellInfo);
};
