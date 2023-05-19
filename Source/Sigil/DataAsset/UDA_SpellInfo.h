

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UDA_SpellMap.h"
#include "UDA_SpellInfo.generated.h"

//UENUM(BlueprintType)
//enum class ESpellTarget : uint8
//{
//	None					UMETA(Hidden),
//	NearestAlly				UMETA(DisplayName = "Nearest Ally"),
//	NearestHostile			UMETA(DisplayName = "Nearest Hostile"),
//	NearestTarget			UMETA(DisplayName = "Nearest Target"),
//	NotApplicable			UMETA(DisplayName = "N/A"),
//	TargetLockOn			UMETA(DisplayName = "Target Lock-on"),
//};
//ENUM_RANGE_BY_FIRST_AND_LAST(ESpellTarget, ESpellTarget::NearestAlly, ESpellTarget::TargetLockOn)
//
//USTRUCT(BlueprintType)
//struct FSpellElements
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		EMagicElementType ElementType;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		float DamageAmount;
//};
//
//USTRUCT(BlueprintType)
//struct FSpellProperties
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		FName Name;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		UTexture2D* Thumbnail;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		//UStaticMesh* Mesh;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		USoundWave* CastSFX;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		USoundWave* HitSFX;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetOptions = "ESpellForm"), Category = "Spell Details")
//		ESpellForm Form;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
//		float BaseMPCost;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
//		float BaseSpeed;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
//		float BaseAcceleration;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
//		TArray<FSpellElements> BaseSpellDamage;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		float MPCostMultiplier = 1.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		float DamageMultiplier = 1.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		float SpeedMultiplier = 1.0f;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
//		bool bIsHoming;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetOptions = "ESpellTarget"), Category = "Spell Details")
//		ESpellTarget Target;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Final Stats")
//		float MPCost;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Final Stats")
//		float Speed;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Final Stats")
//		TArray<FSpellElements> SpellDamage;
//};

/**
 * 
 */
UCLASS(BlueprintType)
class SIGIL_API UDA_SpellInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDA_SpellMap* SpellMap;

	UFUNCTION(BlueprintCallable)
		void SetSpellProperties(FSpellProperties InSpellProperties);

	UFUNCTION(BlueprintCallable)
		FSpellProperties GetSpellProperties();

	UPROPERTY(BlueprintReadWrite)
		bool bCanEdit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		UTexture2D* Thumbnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell Details")
		UStaticMesh* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spell Details")
		FMagicElementMaterials MagicElementMaterials;

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

protected:

	void CalculateMPCost() { MPCost = BaseMPCost * MPCostMultiplier; }
	void CalculateSpellDamage();
	void CalculateSpeed() { Speed = BaseSpeed * SpeedMultiplier; }

	//One function to initiate the calculations
	UFUNCTION(BlueprintCallable)
		void CalculateFinalStats();

	UFUNCTION()
		void SpellMapUpdate();
};
