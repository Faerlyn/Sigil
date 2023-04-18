


#include "MagicShieldActor.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraComponent.h"

#include "Character/SigilCharacter.h"
#include "Component/CharacterAttributesComponent.h"

// Sets default values
AMagicShieldActor::AMagicShieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShieldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield Mesh"));
	ShieldNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Shield FX"));

	SetRootComponent(ShieldMeshComponent);
	
}

// Called when the game starts or when spawned
void AMagicShieldActor::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AMagicShieldActor::ShieldReceiveAnyDamage);

	if (bIsActive)
	{
		ActivateShield();
	}
	else
	{
		DeactivateShield();
	}
	
}

void AMagicShieldActor::ShieldReceiveAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//Try to cast this actor's owner to SigilCharacter
	if (ASigilCharacter* SC = Cast<ASigilCharacter>(GetOwner()))
	{
		//Validate CharacterAttributesComponent
		if (SC->GetCharacterAttributesComponent())
		{
			float ReducedDamage = Damage - (Damage * (DamageReductionPercent / 100.0f));
			float StaminaDamage = ReducedDamage - (ReducedDamage * (BlockEfficiencyPercent / 100.0f));

			SC->GetCharacterAttributesComponent()->ReduceStaminaPoints(StaminaDamage);
			SC->GetCharacterAttributesComponent()->ReduceMagicPoints(StaminaDamage);

			UGameplayStatics::ApplyDamage(SC, ReducedDamage, InstigatedBy, DamageCauser, DamageType->GetClass());

			UGameplayStatics::SpawnSoundAtLocation(this, ShieldBlockSFX, GetActorLocation(), FRotator(0, 0, 0), 1.0f, UKismetMathLibrary::RandomFloatInRange(0.6f, 1.4f), 0.0f, ShieldAttenuationSettings, nullptr, true);

		}
	}
}

void AMagicShieldActor::ActivateShield()
{
	if (!bIsActive)
	{
		if (ShieldMeshComponent)
		{
			ShieldMeshComponent->SetVisibility(true, false);
			ShieldMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		
		if (ShieldNiagaraComponent)
		{
			ShieldNiagaraComponent->Activate();
		}

		bIsActive = true;
	}
}

void AMagicShieldActor::DeactivateShield()
{
	if (bIsActive)
	{
		if (ShieldMeshComponent)
		{
			ShieldMeshComponent->SetVisibility(false, false);
			ShieldMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		if (ShieldNiagaraComponent)
		{
			ShieldNiagaraComponent->Deactivate();
		}

		bIsActive = false;
	}
}

// Called every frame
void AMagicShieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

