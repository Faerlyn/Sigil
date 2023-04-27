

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Library/Struct/SpellStructs.h"
#include "UDA_SpellMap.generated.h"

//UENUM(BlueprintType)
//enum class EMagicElementType : uint8
//{
//	None			UMETA(Hidden),
//	Aether			UMETA(DisplayName = "Aether"),
//	Air				UMETA(DisplayName = "Air"),
//	Dark			UMETA(DisplayName = "Dark"),
//	Earth			UMETA(DisplayName = "Earth"),
//	Fire			UMETA(DisplayName = "Fire"),
//	Light			UMETA(DisplayName = "Light"),
//	Metal			UMETA(DisplayName = "Metal"),
//	Nature			UMETA(DisplayName = "Nature"),
//	Water			UMETA(DisplayName = "Water"),
//};
//ENUM_RANGE_BY_FIRST_AND_LAST(EMagicElementType, EMagicElementType::Aether, EMagicElementType::Water)
//
//UENUM(BlueprintType)
//enum class ESpellForm : uint8
//{
//	None			UMETA(Hidden),
//	Aura			UMETA(DisplayName = "Aura"),
//	Breath			UMETA(DisplayName = "Breath"),
//	Dart			UMETA(DisplayName = "Dart"),
//	Enchant			UMETA(DisplayName = "Enchant"),
//	Flare			UMETA(DisplayName = "Flare"),
//	Orb				UMETA(DisplayName = "Orb"),
//	Ray				UMETA(DisplayName = "Ray"),
//	Vortex			UMETA(DisplayName = "Vortex"),
//	Wall			UMETA(DisplayName = "Wall"),
//	Weapon			UMETA(DisplayName = "Weapon"),
//};
//ENUM_RANGE_BY_FIRST_AND_LAST(ESpellForm, ESpellForm::Aura, ESpellForm::Weapon)
//
//USTRUCT(BlueprintType)
//struct FSpellFormData
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		UStaticMesh* FormMesh;
//};
//
//USTRUCT(BlueprintType)
//struct FMagicElementMaterials
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		UMaterialInstance* MagicElementMaterial;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		UMaterialInstance* MagicElementMaterialEmissive;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		FLinearColor MagicPrimaryColour;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		FLinearColor MagicSecondaryColour;
//};

/**
 * 
 */
UCLASS()
class SIGIL_API UDA_SpellMap : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<ESpellForm, FSpellFormData> SpellForms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<EMagicElementType, FMagicElementMaterials> MagicElementMaterials;
	
};
