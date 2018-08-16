#pragma once

#include "MLPrototyping_Types.h"
#include "Point.h"
#include "Sequence.h"

namespace MLPrototyping
{
	struct FNormalDataParameters
	{
		using FPoint = TPoint<2, real_t>;

		size_t N;
		real_t SD, Norm;
		FPoint Mean;
	};

	struct FHyperRingDataParameters
	{
		using FPoint = TPoint<2, real_t>;

		size_t N;
		real_t SD, Readius, Norm;
		FPoint Mean;
	};

	struct FGammaDataParameters
	{
		using FPoint = TPoint<2, real_t>;

		size_t N;
		real_t Alpha, Beta, Norm;
		FPoint Mean, Along;
	};
}