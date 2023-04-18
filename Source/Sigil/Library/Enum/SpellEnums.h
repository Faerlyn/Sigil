

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpellEnums.generated.h"

UENUM(BlueprintType)
enum class ESpellTarget : uint8
{
	None					UMETA(Hidden),
	NearestAlly				UMETA(DisplayName = "Nearest Ally"),
	NearestHostile			UMETA(DisplayName = "Nearest Hostile"),
	NearestTarget			UMETA(DisplayName = "Nearest Target"),
	NotApplicable			UMETA(DisplayName = "N/A"),
	TargetLockOn			UMETA(DisplayName = "Target Lock-on"),
};
ENUM_RANGE_BY_FIRST_AND_LAST(ESpellTarget, ESpellTarget::NearestAlly, ESpellTarget::TargetLockOn)

UENUM(BlueprintType)
enum class EMagicElementType : uint8
{
	None			UMETA(Hidden),
	Aether			UMETA(DisplayName = "Aether"),
	Air				UMETA(DisplayName = "Air"),
	Dark			UMETA(DisplayName = "Dark"),
	Earth			UMETA(DisplayName = "Earth"),
	Fire			UMETA(DisplayName = "Fire"),
	Light			UMETA(DisplayName = "Light"),
	Metal			UMETA(DisplayName = "Metal"),
	Nature			UMETA(DisplayName = "Nature"),
	Water			UMETA(DisplayName = "Water"),
};
ENUM_RANGE_BY_FIRST_AND_LAST(EMagicElementType, EMagicElementType::Aether, EMagicElementType::Water)

UENUM(BlueprintType)
enum class ESpellForm : uint8
{
	None			UMETA(Hidden),
	Aura			UMETA(DisplayName = "Aura"),
	Breath			UMETA(DisplayName = "Breath"),
	Dart			UMETA(DisplayName = "Dart"),
	Enchant			UMETA(DisplayName = "Enchant"),
	Flare			UMETA(DisplayName = "Flare"),
	Orb				UMETA(DisplayName = "Orb"),
	Ray				UMETA(DisplayName = "Ray"),
	Vortex			UMETA(DisplayName = "Vortex"),
	Wall			UMETA(DisplayName = "Wall"),
	Weapon			UMETA(DisplayName = "Weapon"),
};
ENUM_RANGE_BY_FIRST_AND_LAST(ESpellForm, ESpellForm::Aura, ESpellForm::Weapon)

/**
 * 
 */
UCLASS()
class SIGIL_API USpellEnums : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
