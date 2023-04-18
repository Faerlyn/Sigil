

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SigilTargetingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USigilTargetingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIGIL_API ISigilTargetingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/// <summary>
	/// Outputs information from an actor that is used by SigilCharacter's targeting system
	/// </summary>
	/// <param name="NewTarget">A reference to the targetable actor</param>
	/// <param name="NewTargetName">The actor's name</param>
	/// <param name="NewTargetMessage">A message that describes who or what the actor is</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GetActorTargetInfo)
		void GetActorTargetInfo(AActor* &NewTarget, FName &NewTargetName, FText &NewTargetMessage);

	/// <summary>
	/// Returns a component of type UPrimitiveComponent determined by the actor that implements this interface
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GetTargetComponent)
		UPrimitiveComponent* GetTargetComponent();

	/*
	Implement the interface with these functions: 
	
	void GetActorTargetInfo_Implementation(AActor*& NewTarget, FName& NewTargetName, FText& NewTargetMessage) override;
	UPrimitiveComponent* GetTargetComponent_Implementation() override;
	*/
};
