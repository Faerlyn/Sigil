

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UDA_SpellInfo.generated.h"

UENUM(BlueprintType)
enum class EMagicElementType : uint8
{
	Aether			UMETA(DisplayName = "Aether"),
	Air				UMETA(DisplayName = "Air"),
	Earth			UMETA(DisplayName = "Earth"),
	Fire			UMETA(DisplayName = "Fire"),
	Water			UMETA(DisplayName = "Water"),
};

USTRUCT(BlueprintType)
struct FSpellDamage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EMagicElementType Element;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DamageAmount;
};

/**
 * 
 */
UCLASS()
class SIGIL_API UDA_SpellInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MPCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsHoming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSpellDamage> SpellDamage;
};
