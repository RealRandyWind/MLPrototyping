#pragma once;

#include "NDev.h"

namespace MLPrototypingTest
{
	using namespace NDev;
	using namespace NDev::Types;

	template<FSize SizeFeature, FSize SizeLabel>
	struct TModelStub : TModel<SizeFeature, SizeLabel>
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		struct FParameters
		{
			FReal Alpha, Weight, Difference;
			FSize Size;
		};

		struct FState
		{
			TSequence<FReal> Weights;
			typename FModel::FLabel Difference;
		};

		FParameters Parameters;
		FState State;


	protected:
		virtual FVoid _Initialize() override
		{
			State.Weights.Reserve(Parameters.Size, True);
			for (auto &Weight : State.Weights)
			{
				Weight = Parameters.Alpha;
			}

			State.Difference = Parameters.Difference;
		}

		virtual FVoid _Use(const typename FModel::FFeature &Feature, typename FModel::FLabel &Label, FBoolean bTraning) override
		{
			Label = Sum(Feature);
		}

		virtual FVoid _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
		{
			State.Difference = Sample.Label - Label;
		}

		virtual FVoid _Optimize(const typename FModel::FSample &Sample) override
		{
			State.Difference += Parameters.Weight * (Sum(Sample.Label) + Sum(Sample.Feature));
		}

		virtual FVoid _Optimize() override
		{
			State.Difference *= Parameters.Weight;
		}


	};



}