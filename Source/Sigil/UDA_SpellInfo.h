

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UDA_SpellInfo.generated.h"

UENUM(BlueprintType)
enum class EMagicElementType : uint8
{
	None			UMETA(Hidden),
	Aether			UMETA(DisplayName = "Aether"),
	Air				UMETA(DisplayName = "Air"),
	Earth			UMETA(DisplayName = "Earth"),
	Fire			UMETA(DisplayName = "Fire"),
	Water			UMETA(DisplayName = "Water"),
	Dark			UMETA(DisplayName = "Dark"),
	Light			UMETA(DisplayName = "Light"),
	Metal			UMETA(DisplayName = "Metal"),
	Nature			UMETA(DisplayName = "Nature"),
};

UENUM(BlueprintType)
enum class ESpellForm : uint8
{
	None			UMETA(Hidden),
	Dart			UMETA(DisplayName = "Dart"),
	Orb				UMETA(DisplayName = "Orb"),
	Ray				UMETA(DisplayName = "Ray"),
	Breath			UMETA(DisplayName = "Breath"),
	Weapon			UMETA(DisplayName = "Weapon"),
	Enchant			UMETA(DisplayName = "Enchant"),
	Wall			UMETA(DisplayName = "Wall"),
	Vortex			UMETA(DisplayName = "Vortex"),
	Aura			UMETA(DisplayName = "Aura"),
};

UENUM(BlueprintType)
enum class ESpellTarget : uint8
{
	None					UMETA(Hidden),
	NotApplicable			UMETA(DisplayName = "N/A"),
	TargetLockOn			UMETA(DisplayName = "Target Lock-on"),
	NearestTarget			UMETA(DisplayName = "Nearest Target"),
	NearestAlly				UMETA(DisplayName = "Nearest Ally"),
	NearestHostile			UMETA(DisplayName = "Nearest Hostile"),
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		UStaticMesh* Mesh;

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

/**
 * 
 */
UCLASS(BlueprintType)
class SIGIL_API UDA_SpellInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION(BlueprintCallable)
		void SetSpellProperties(FSpellProperties InSpellProperties);

	UFUNCTION(BlueprintCallable)
		FSpellProperties GetSpellProperties();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanEdit = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell Details")
		UStaticMesh* Mesh;

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
};
