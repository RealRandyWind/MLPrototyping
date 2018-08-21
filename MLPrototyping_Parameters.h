#pragma once

#include "MLPrototyping_Types.h"
#include "Point.h"
#include "Sequence.h"
#include "Model.h"

namespace MLPrototyping
{
	struct FNormalDataParameters
	{
		using FModel = TModel<2, 3>;
		using FFeature = FModel::FFeature;
		using FLabel = FModel::FLabel;
		using FSample = FModel::FSample;

		size_t N;
		real_t SD, Norm;
		FFeature Mean;
		FLabel Label;

		static FNormalDataParameters Default()
		{
			FNormalDataParameters Item;
			Item.N = 1024;
			Item.SD = 1;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	struct FRingDataParameters
	{
		using FModel = TModel<2, 3>;
		using FFeature = FModel::FFeature;
		using FLabel = FModel::FLabel;
		using FSample = FModel::FSample;

		size_t N;
		real_t SD, Readius, Norm;
		FFeature Mean;
		FLabel Label;

		static FRingDataParameters Default()
		{
			FRingDataParameters Item;
			Item.N = 1024;
			Item.SD = .5;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Readius = 1;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	struct FGammaDataParameters
	{
		using FModel = TModel<2, 3>;
		using FFeature = FModel::FFeature;
		using FLabel = FModel::FLabel;
		using FSample = FModel::FSample;

		size_t N;
		real_t Alpha, Beta, Norm;
		FFeature Mean, Along;
		FLabel Label;

		static FGammaDataParameters Default()
		{
			FGammaDataParameters Item;
			Item.N = 1024;
			Item.Alpha = 1.5;
			Item.Beta = 2;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Along = 0;
			Item.Along[0] = 1;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};
}