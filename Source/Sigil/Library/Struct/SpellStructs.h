

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Enum/SpellEnums.h"
#include "SpellStructs.generated.h"

USTRUCT(BlueprintType)
struct FSpellElements
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EMagicElementType ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageAmount;
};

USTRUCT(BlueprintType)
struct FSpellProperties
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		UTexture2D* Thumbnail;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		//UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		USoundWave* CastSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		USoundWave* HitSFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetOptions = "ESpellForm"), Category = "Spell Details")
		ESpellForm Form;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float BaseMPCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float BaseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float BaseAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		TArray<FSpellElements> BaseSpellDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		float MPCostMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		float DamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		float SpeedMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		bool bIsHoming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetOptions = "ESpellTarget"), Category = "Spell Details")
		ESpellTarget Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Final Stats")
		float MPCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Final Stats")
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Final Stats")
		TArray<FSpellElements> SpellDamage;
};

USTRUCT(BlueprintType)
struct FSpellFormMeshes
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* FormMesh;
};

USTRUCT(BlueprintType)
struct FMagicElementMaterials
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* MagicElementMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMaterialInstance* MagicElementMaterialEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FLinearColor MagicPrimaryColour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FLinearColor MagicSecondaryColour;
};

/**
 * 
 */
UCLASS()
class SIGIL_API USpellStructs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
