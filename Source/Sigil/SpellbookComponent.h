

#pragma once

#include "CoreMinimal.h"
#include "UDA_SpellInfo.h"
#include "Components/ActorComponent.h"
#include "SpellbookComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIGIL_API USpellbookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellbookComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		TArray<UDA_SpellInfo*> PlayerSpells;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		TArray<UDA_SpellInfo*> GetPlayerSpells() { return PlayerSpells; }

	UFUNCTION(BlueprintCallable)
		void SetPlayerSpells(TArray<UDA_SpellInfo*> NewPlayerSpells) { PlayerSpells = NewPlayerSpells; }
	
	UFUNCTION(BlueprintCallable)
		void AddSpellToSpellbook(UDA_SpellInfo* InSpellInfo);

	UFUNCTION(BlueprintCallable)
		bool RemoveSpellFromSpellbook(UDA_SpellInfo* InSpellInfo);
};