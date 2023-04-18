


#include "SigilCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetTextLibrary.h"

#include "../../Actor/MagicShieldActor.h"
#include "../../Actor/SpellProjectileActor.h"
#include "../../Actor/Component/CharacterAttributesComponent.h"
#include "../../Actor/Component/SigilDamageHandlerComponent.h"
#include "../../Actor/Component/SpellcastingComponent.h"
#include "../../DataAsset/UDA_SpellInfo.h"

static TAutoConsoleVariable<bool> CVarDisplayTrace(
	TEXT("Tantrum.Character.Debug.DisplayTrace"),
	false,
	TEXT("Display Trace"),
	ECVF_Default);

// Sets default values
ASigilCharacter::ASigilCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterAttributesComponent = CreateDefaultSubobject<UCharacterAttributesComponent>(TEXT("Character Attributes Component"));
	SpellcastingComponent = CreateDefaultSubobject<USpellcastingComponent>(TEXT("Spellcasting Component"));
	DamageHandlerComponent = CreateDefaultSubobject<USigilDamageHandlerComponent>(TEXT("Damage Handler Component"));

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	ProjectileArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Projectile Arm"));
	ShieldArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Shield Arm"));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));

	ShieldArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Shield Start"));
	TargetArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Target"));
	ProjectileArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Start"));

	/*
		Attach the components to the character:
		- CharacterMesh
			- TargetArrow
			- ShieldArm
				- ShieldArrow
			- ProjectileArm
				- ProjectileArrow
			- CameraArm
				- FollowCamera
	*/

	if (CameraArm)
	{
		CameraArm->SetupAttachment(GetMesh());

		if (FollowCamera)
		{
			FollowCamera->SetupAttachment(CameraArm);
		}
	}

	if (ProjectileArm)
	{
		ProjectileArm->SetupAttachment(GetMesh());

		if (ProjectileArrow)
		{
			ProjectileArrow->SetupAttachment(ProjectileArm);
		}
	}

	if (ShieldArm)
	{
		ShieldArm->SetupAttachment(GetMesh());

		if (ShieldArrow)
		{
			ShieldArrow->SetupAttachment(ShieldArm);
		}
	}

	if (TargetArrow)
	{
		TargetArrow->SetupAttachment(GetMesh(), "TargetSocket");
	}

	//Bind SigilReceiveAnyDamage to the OnTakeAnyDamage delegate
	OnTakeAnyDamage.AddDynamic(this, &ASigilCharacter::SigilReceiveAnyDamage);

	if (CharacterAttributesComponent)
	{
		CharacterAttributesComponent->OnHitPointsReachedZero.AddDynamic(this, &ASigilCharacter::OnDeath);
	}
	
}

// Called when the game starts or when spawned
void ASigilCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASigilCharacter::GetActorTargetInfo_Implementation(AActor* &NewTarget, FName &NewTargetName, FText &NewTargetMessage)
{
	NewTarget = this;
	NewTargetName = FName("Sigil Player Character");
	NewTargetMessage = FText::FromString("I am a player character");
}

UPrimitiveComponent* ASigilCharacter::GetTargetComponent_Implementation()
{
	//Validate TargetArrow
	if (TargetArrow)
	{
		//Return TargetArrow
		return TargetArrow;
	}

	return nullptr;
}

void ASigilCharacter::SigilReceiveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//Validate DamageHandlerComponent
	if (DamageHandlerComponent)
	{
		//Call TakeDamage
		DamageHandlerComponent->TakeDamage(Damage, InstigatedBy, DamageCauser, DamageType);
	}
}

// Called every frame
void ASigilCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If bIsCameraLocked is true
	if (bIsCameraLocked)
	{
		//Call LockCameraToTarget
		LockCameraToTarget();
	}
}

// Called to bind functionality to input
void ASigilCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ASigilCharacter::TargetTrace(UPrimitiveComponent*& NewTargetComponent)
{
	//Get the player viewpoint and store the output into two variables
	FVector Location;
	FRotator Rotation;

	GetController()->GetPlayerViewPoint(Location, Rotation);
	
	//Get the player's forward vector
	FVector PlayerViewForward = Rotation.Vector();

	//AdditionalDistance is the distance from the player's camera to the player character's location
	const float AdditionalDistance = (Location - GetActorLocation()).Size();

	//Get the start position of the trace
	FVector StartPos = Location + (PlayerViewForward * (AdditionalDistance));

	//Get the end position of the trace
	FVector EndPos = StartPos + (PlayerViewForward * (TraceLength));

	//Get the player character's forward vector
	FVector CharacterForward = GetActorForwardVector();

	/* Might need this code in the future
	//Return nullptr if trying to target something behind the player character
	float DotResult = FVector::DotProduct(PlayerViewForward, CharacterForward);

	if (DotResult < -0.23)
	{
		return CurrentTargetComponentRef = nullptr;
	}*/

	FHitResult HitResult;

	EDrawDebugTrace::Type DebugTrace;

	//If CVarDisplayTrace is true, 
	if (CVarDisplayTrace->GetBool())
	{
		//Set DebugTrace to draw the trace
		DebugTrace = EDrawDebugTrace::Persistent;
	}
	else
	{
		//Set DebugTrace to not draw the trace
		DebugTrace = EDrawDebugTrace::None;
	}

	//Create an array of type AActor which the trace will ignore, add the player character to this.
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), StartPos, EndPos, 15.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel11), false, ActorsToIgnore, DebugTrace, HitResult, true);

	//If CVarDisplayTrace is true, draw the trace
#if ENABLE_DRAW_DEBUG
	if (CVarDisplayTrace->GetBool())
	{
		static float FovDeg = 90.0f;
		DrawDebugCamera(GetWorld(), Location, Rotation, FovDeg);
		DrawDebugLine(GetWorld(), Location, EndPos, HitResult.bBlockingHit ? FColor::Red : FColor::White);
		DrawDebugPoint(GetWorld(), EndPos, 70.0f, HitResult.bBlockingHit ? FColor::Red : FColor::White);
	}
#endif

	//Call SetNewTarget, passing in the hit actor and NewTargetComponent. The function will return true if it is able to set CurrentTargetComponentRef.
	return SetNewTarget(HitResult.GetActor(), NewTargetComponent);
}

void ASigilCharacter::RemoveTarget()
{
	//Set CurrentTargetRef and CurrentTargetComponentRef to nullptr
	CurrentTargetRef = nullptr;
	CurrentTargetComponentRef = nullptr;
}

bool ASigilCharacter::SetNewTarget(AActor* NewTargetActor, UPrimitiveComponent* &NewTargetComponent)
{
	//If the hit actor implements USigilTargetingInterface
	if (UKismetSystemLibrary::DoesImplementInterface(NewTargetActor, USigilTargetingInterface::StaticClass()))
	{
		FName NewTargetName;
		FText NewTargetMessage;

		//Call GetActorTargetInfo
		ISigilTargetingInterface::Execute_GetActorTargetInfo(NewTargetActor, CurrentTargetRef, NewTargetName, NewTargetMessage);

		//Set NewTargetComponent by calling GetTargetComponent
		NewTargetComponent = ISigilTargetingInterface::Execute_GetTargetComponent(NewTargetActor);

		//Print the target's name
		UKismetSystemLibrary::PrintText(this, UKismetTextLibrary::Conv_NameToText(NewTargetName), true, true, FLinearColor::Yellow, 2.0f, "1");

		//Print the target's message
		UKismetSystemLibrary::PrintText(this, NewTargetMessage, true, true, FLinearColor::Yellow, 2.0f, "2");

		//If NewTargetComponent is valid
		if (NewTargetComponent)
		{
			//Set CurrentTargetComponentRef to NewTargetComponent
			CurrentTargetComponentRef = NewTargetComponent;

			//Return true
			return true;
		}
	}

	//Set NewTargetComponent to nullptr and return false
	NewTargetComponent = nullptr;
	return false;
}

void ASigilCharacter::LockCameraToTarget()
{
	//Validate FollowCamera
	if (FollowCamera)
	{
		//Validate CurrentTargetComponentRef
		if (CurrentTargetComponentRef)
		{
			//FRotator Current, Target, NewRotation;

			//Get the player controller's control rotation
			FRotator Current = GetController()->GetControlRotation();

			//Find the LookAt rotation using FollowCamera's location as the start and CurrentTargetComponentRef's location as the target
			FRotator Target = UKismetMathLibrary::FindLookAtRotation(FollowCamera->GetComponentLocation(), CurrentTargetComponentRef->GetComponentLocation());

			//Make the controller slowly Interp to the target rotation
			FRotator NewRotation = UKismetMathLibrary::RInterpTo(Current, Target, GetWorld()->GetDeltaSeconds(), 5.0f);
			GetController()->SetControlRotation(NewRotation);
		}
	}
}

//void ASigilCharacter::DisengageCameraLockOn()
//{
//	SetCameraLockOn(false);
//}

void ASigilCharacter::ToggleCameraLockOn()
{
	//If bIsCameraLocked is true
	if (bIsCameraLocked)
	{
		//Call SetCameraLockOn, passing in false
		SetCameraLockOn(false);
	}
	else
	{
		//Call SetCameraLockOn, passing in true
		SetCameraLockOn(true);
	}
}

void ASigilCharacter::SetCameraLockOn(bool InBool)
{
	//If bIsCameraLocked is not equal to InBool
	if (bIsCameraLocked != InBool)
	{
		//Set bIsCameraLocked to InBool
		bIsCameraLocked = InBool;
	}
}

bool ASigilCharacter::HasValidTarget()
{
	//If CurrentTargetRef is valid
	if (CurrentTargetRef)
	{
		//Return true
		return true;
	}
	else
	{
		//Return false
		return false;
	}
}

AActor* ASigilCharacter::GetCurrentTargetRef()
{
	//If CurrentTargetRef is valid
	if (CurrentTargetRef)
	{
		//Return CurrentTargetRef
		return CurrentTargetRef;
	}

	return nullptr;
}

void ASigilCharacter::OnDeath()
{
	//Get the mesh and set simulate physics to true
	GetMesh()->SetSimulatePhysics(true);
}

void ASigilCharacter::ExecutePrimaryAction()
{
	//Validate SpellProjectileBP
	if (SpellProjectileBP)
	{
		//If the character's currently equipped spell is valid
		if (UDA_SpellInfo* EquippedSpell = SpellcastingComponent->GetEquippedSpell())
		{
			//Validate the CharacterAttributesComponent
			if (CharacterAttributesComponent)
			{
				//If the player's current magic points are greater than or equal to the MPCost of the equipped spell
				if (CharacterAttributesComponent->GetCurrentMagicPoints() >= EquippedSpell->MPCost)
				{
					//Validate ProjectileArrow
					if (ProjectileArrow)
					{
						//Get ProjectileArrow's transform
						FTransform Transform = ProjectileArrow->GetComponentTransform();

						//Spawn a deferred actor of type ASpellProjectileActor
						if (ASpellProjectileActor* SpellProjectile = GetWorld()->SpawnActorDeferred<ASpellProjectileActor>(SpellProjectileBP, Transform, this, this, ESpawnActorCollisionHandlingMethod::Undefined))
						{
							//Initialise SpellProjectile's variables
							SpellProjectile->SetInitialVariables(EquippedSpell, CurrentTargetComponentRef);

							//Finish spawning the actor
							SpellProjectile->FinishSpawning(Transform);

							//Reduce the player's magic points by an amount equal to the MPCost of the equipped spell
							CharacterAttributesComponent->ReduceMagicPoints(EquippedSpell->MPCost);
						}
					}
				}
			}
		}
	}
}

void ASigilCharacter::ExecuteSecondaryAction()
{
	//Validate MagicShieldBP	
	if (MagicShieldBP)
	{
		//Validate MagicShieldRef
		if (MagicShieldRef)
		{
			//If the shield is active
			if (MagicShieldRef->GetIsActive())
			{
				//Call DeactivateShield				
				MagicShieldRef->DeactivateShield();
			}
			else
			{
				//Call ActivateShield
				MagicShieldRef->ActivateShield();
			}
		}
		else
		{
			//Configure actor spawning parameters
			FActorSpawnParameters ShieldSpawnParams;
			ShieldSpawnParams.Name = "Player Shield";
			ShieldSpawnParams.Owner = this;
			ShieldSpawnParams.Instigator = this;

			//Validate ShieldArrow
			if (ShieldArrow)
			{
				//Get ShieldArrow's transform
				FTransform Transform = ShieldArrow->GetComponentTransform();

				//Spawn a deferred actor of type AMagicShieldActor
				if (AMagicShieldActor* MagicShield = GetWorld()->SpawnActorDeferred<AMagicShieldActor>(MagicShieldBP, Transform, this, this, ESpawnActorCollisionHandlingMethod::Undefined))
				{
					//Configure attachment transform rules
					FAttachmentTransformRules ShieldAttachRules(EAttachmentRule::KeepWorld, true);
					ShieldAttachRules.ScaleRule = EAttachmentRule::KeepRelative;

					//Attach MagicShield to ShieldArrow
					MagicShield->AttachToComponent(ShieldArrow, ShieldAttachRules);

					//Add MagicShield to the CapsuleComponent's IgnoreActorWhenMoving array
					GetCapsuleComponent()->IgnoreActorWhenMoving(MagicShield, true);

					//Finish spawning the actor
					MagicShield->FinishSpawning(Transform);

					//Set MagicShieldRef to MagicShield
					MagicShieldRef = MagicShield;
				}
			}
		}
	}
}
