#pragma once

#include <random>

#include "NDevTypes.h"
#include "NDevPoint.h"
#include "NDevMathPoint.h"


namespace NDev
{
    using namespace Types;

    template<typename Type>
	struct TDistribution
	{
		Type &operator()(Type &Value) { Value = Next();  return Value; }

		template<FSize SizeLhs>
		TPoint<SizeLhs, Type> &operator()(TPoint<SizeLhs, Type> &Point)
		{
			for (auto &Value : Point) { Value = Next(); }
			return Point;
		}

		Type operator()() { return Next(); }

		template<FSize SizeLhs>
		TPoint<SizeLhs, Type> operator()()
		{
			TPoint<SizeLhs, Type> Point;

			for (auto &Value : Point) { Value = Next(); }
			return Point;
		}

		virtual FVoid Seed(FSize SeedIn) = 0;

		virtual Type Next() = 0;

		virtual FVoid Reset() = 0;
	};

	template<typename Type>
	struct TNormal : TDistribution<Type>
	{
		std::default_random_engine Generator;

		std::normal_distribution<Type> Distribution;

		TNormal()
		{
			Generator = std::default_random_engine();
			Distribution = std::normal_distribution<Type>();
		}

		~TNormal() { }

		FVoid Parameters(Type Mean, Type SD)
		{
			Distribution.param(std::normal_distribution<Type>::param_type(Mean, SD));
		}

		virtual FVoid Seed(FSize SeedIn) override
		{
			return Generator.seed(static_cast<unsigned int>(SeedIn));
		}

		virtual Type Next() override
		{
			return Distribution(Generator);
		}

		virtual FVoid Reset() override
		{
			Distribution.reset();
		}
	};

	template<typename Type>
	struct TGamma : TDistribution<Type>
	{
		std::default_random_engine Generator;

		std::gamma_distribution<Type> Distribution;

		TGamma()
		{
			Generator = std::default_random_engine();
			Distribution = std::gamma_distribution<Type>();
		}

		~TGamma() { }

		FVoid Parameters(Type Alpha, Type Beta)
		{
			Distribution.param(std::gamma_distribution<Type>::param_type(Alpha, Beta));
		}

		virtual FVoid Seed(FSize SeedIn) override
		{
			return Generator.seed(static_cast<unsigned int>(SeedIn));
		}

		virtual Type Next() override
		{
			return Distribution(Generator);
		}

		virtual FVoid Reset() override
		{
			Distribution.reset();
		}
	};

	template<typename Type>
	struct TUniform : TDistribution<Type>
	{
		std::default_random_engine Generator;

		std::uniform_real_distribution<Type> Distribution;

		TUniform()
		{
			Generator = std::default_random_engine();
			Distribution = std::uniform_real_distribution<Type>();
		}

		~TUniform() { }

		FVoid Parameters(Type Lower, Type Upper)
		{
			Distribution.param(std::uniform_real_distribution<Type>::param_type(Lower, Upper));
		}

		virtual FVoid Seed(FSize SeedIn) override
		{
			return Generator.seed(static_cast<unsigned int>(SeedIn));
		}

		virtual Type Next() override
		{
			return Distribution(Generator);
		}

		virtual FVoid Reset() override
		{
			Distribution.reset();
		}
	};
}