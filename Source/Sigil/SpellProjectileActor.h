

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UDA_SpellInfo.h"
#include "SpellProjectileActor.generated.h"

UCLASS()
class SIGIL_API ASpellProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn=true))
		UDA_SpellInfo* SpellDataAsset;

};
