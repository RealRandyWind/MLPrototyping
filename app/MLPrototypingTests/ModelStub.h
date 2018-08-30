#pragma once;


#include "MLPrototyping_Definitions.h"
#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "Model.h"
#include "Point.h"
#include "Sequence.h"

using namespace MLPrototyping;

namespace MLPrototypingTest
{
	template<size_t SizeFeature, size_t SizeLabel>
	struct TModelStub : TModel<SizeFeature, SizeLabel>
	{
		struct FParameters
		{
			real_t Alpha, Weight, Difference;
			size_t Size;
		};

		struct FState
		{
			TSequence<real_t> Weights;
			FLabel Difference;
		};

		FParameters Parameters;
		FState State;


	protected:
		virtual void _Initialize() override
		{
			State.Weights.Reserve(Parameters.Size, true);
			for (auto &Weight : State.Weights)
			{
				Weight = Parameters.Alpha;
			}

			State.Difference = Parameters.Difference;
		}

		virtual void _Use(const FFeature &Feature, FLabel &Label, bool_t bTraning) override
		{
			Label = Sum(Feature);
		}

		virtual void _Train(const FLabel &Label, const FSample &Sample) override
		{
			State.Difference = Sample.Label - Label;
		}

		virtual void _Optimize(const FSample &Sample) override
		{
			State.Difference += Parameters.Weight * (Sum(Sample.Label) + Sum(Sample.Feature));
		}

		virtual void _Optimize() override
		{
			State.Difference *= Parameters.Weight;
		}


	};



}