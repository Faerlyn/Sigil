

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

};
