


#include "UDA_SpellInfo.h"

void UDA_SpellInfo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (!bIsHoming)
	{
		Target = ESpellTarget::NotApplicable;
	}

	SpellMapUpdate();

	CalculateFinalStats();
}

void UDA_SpellInfo::SetSpellProperties(FSpellProperties InSpellProperties)
{
	if (bCanEdit)
	{
		Name = InSpellProperties.Name;
		Thumbnail = InSpellProperties.Thumbnail;
		//Mesh = InSpellProperties.Mesh;
		CastSFX = InSpellProperties.CastSFX;
		HitSFX = InSpellProperties.HitSFX;
		Form = InSpellProperties.Form;
		BaseMPCost = InSpellProperties.BaseMPCost;
		BaseSpeed = InSpellProperties.BaseSpeed;
		BaseAcceleration = InSpellProperties.BaseAcceleration;
		BaseSpellDamage = InSpellProperties.BaseSpellDamage;
		MPCostMultiplier = InSpellProperties.MPCostMultiplier;
		DamageMultiplier = InSpellProperties.DamageMultiplier;
		SpeedMultiplier = InSpellProperties.SpeedMultiplier;
		bIsHoming = InSpellProperties.bIsHoming;
		Target = InSpellProperties.Target;

		SpellMapUpdate();
		CalculateFinalStats();
	}
}

FSpellProperties UDA_SpellInfo::GetSpellProperties()
{
	FSpellProperties OutSpellProperties;

	OutSpellProperties.Name = Name;
	OutSpellProperties.Thumbnail = Thumbnail;
	//OutSpellProperties.Mesh = Mesh;
	OutSpellProperties.CastSFX = CastSFX;
	OutSpellProperties.HitSFX = HitSFX;
	OutSpellProperties.Form = Form;
	OutSpellProperties.BaseMPCost = BaseMPCost;
	OutSpellProperties.BaseSpeed = BaseSpeed;
	OutSpellProperties.BaseAcceleration = BaseAcceleration;
	OutSpellProperties.BaseSpellDamage = BaseSpellDamage;
	OutSpellProperties.MPCostMultiplier = MPCostMultiplier;
	OutSpellProperties.DamageMultiplier = DamageMultiplier;
	OutSpellProperties.SpeedMultiplier = SpeedMultiplier;
	OutSpellProperties.bIsHoming = bIsHoming;
	OutSpellProperties.Target = Target;
	OutSpellProperties.MPCost = MPCost;
	OutSpellProperties.Speed = Speed;
	OutSpellProperties.SpellDamage = SpellDamage;

	return OutSpellProperties;
}

void UDA_SpellInfo::CalculateSpellDamage()
{
	SpellDamage.Empty();

	for (size_t i = 0; i < BaseSpellDamage.Num(); i++)
	{
		//Create new struct that we will pass into SpellDamage
		struct FSpellElements NewSpellDamage {};

		//Set the damage amount to be the base amount times the damage multiplier
		NewSpellDamage.DamageAmount = BaseSpellDamage[i].DamageAmount * DamageMultiplier;

		//Copy across the element from the base
		NewSpellDamage.ElementType = BaseSpellDamage[i].ElementType;

		//Add the new struct to the SpellDamage array
		SpellDamage.Add(NewSpellDamage);
	}
}

void UDA_SpellInfo::CalculateFinalStats()
{
	CalculateMPCost();
	CalculateSpellDamage();
	CalculateSpeed();
}

void UDA_SpellInfo::SpellMapUpdate()
{
	if (SpellMap)
	{
		if (UStaticMesh* NewMesh = SpellMap->SpellForms.FindRef(Form).Mesh)
		{
			Mesh = NewMesh;
		}

		MagicElementMaterials = SpellMap->MagicElementMaterials.FindRef(BaseSpellDamage[0].ElementType);

		/*if (UMaterialInstance* NewMatInst = SpellMap->MagicElementMaterials.FindRef(BaseSpellDamage[0].ElementType).MagicElementMaterial)
		{
			MagicMaterial = NewMatInst;
		}

		if (UMaterialInstance* NewMatInst = SpellMap->MagicElementMaterials.FindRef(BaseSpellDamage[0].ElementType).MagicElementMaterialEmissive)
		{
			MagicMaterialEmissive = NewMatInst;
		}*/
	}
}
