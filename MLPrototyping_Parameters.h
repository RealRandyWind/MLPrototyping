#pragma once

#include "MLPrototyping_Configurations.h"

#include "MLPrototyping_Types.h"
#include "Point.h"
#include "Sequence.h"
#include "Model.h"

namespace MLPrototyping
{
	template<size_t SizeFeature, size_t SizeLabel>
	struct TUniformDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		size_t N;
		real_t Norm, Radius;
		FFeature Mean;
		FLabel Label;

		static TUniformDataParameters<SizeFeature, SizeLabel> Default()
		{
			TUniformDataParameters<SizeFeature, SizeLabel> Item;
			Item.N = 1024;
			Item.Norm = 1;
			Item.Radius = 1;
			Item.Mean = 0;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	template<size_t SizeFeature, size_t SizeLabel>
	struct TNormalDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		size_t N;
		real_t SD, Norm;
		FFeature Mean;
		FLabel Label;

		static TNormalDataParameters<SizeFeature, SizeLabel> Default()
		{
			TNormalDataParameters<SizeFeature, SizeLabel> Item;
			Item.N = 1024;
			Item.SD = 1;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	template<size_t SizeFeature, size_t SizeLabel>
	struct TGammaDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		size_t N;
		real_t Alpha, Beta, Norm;
		FFeature Mean, Along;
		FLabel Label;

		static TGammaDataParameters<SizeFeature, SizeLabel> Default()
		{
			TGammaDataParameters<SizeFeature, SizeLabel> Item;
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
	
	template<size_t SizeFeature, size_t SizeLabel>
	struct TRingDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		size_t N;
		real_t SD, Readius, Norm;
		FFeature Mean;
		FLabel Label;

		static TRingDataParameters<SizeFeature, SizeLabel> Default()
		{
			TRingDataParameters<SizeFeature, SizeLabel> Item;
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



}