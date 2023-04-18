

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

	//The name of the widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText WidgetName;

	//The widget's minimum width
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WidgetMinimumWidth;

	//The widget's minimum height
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WidgetMinimumHeight;

	//Getter for WidgetName
	FText GetWidgetName() { return WidgetName; }
};
