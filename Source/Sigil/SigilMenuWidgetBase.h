

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SigilMenuWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class SIGIL_API USigilMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText WidgetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WidgetMinimumWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WidgetMinimumHeight;

	FText GetWidgetName();
};
