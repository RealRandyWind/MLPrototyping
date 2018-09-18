#pragma once

#include <functional>

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "Model.h"
#include "Sequence.h"

namespace MLPrototyping
{
	namespace LVQ
	{
		template<FSize SizeFeature, FSize SizeLabel>
		struct TNN : public TModel<SizeFeature, SizeLabel>
		{
			using FModel = TModel<SizeFeature, SizeLabel>;

			using FPrototype = typename FModel::FSample;

			struct FNeighbour
			{
				FReal Distance2;
				FPrototype *Prototype;
			};

			using FOnOutput = std::function<void(TSequence<FNeighbour>&, typename FModel::FLabel&)>;

			struct FParameters
			{
				FSize KNearest;
				FOnOutput OnOutput;
			};

			struct FState
			{
				TSequence<FPrototype> Prototypes;
				TSequence<FNeighbour> Neighbours;
			};

			FParameters Parameters;
			FState State;

			FVoid UseDefaultParameters()
			{
				Parameters.KNearest = 3;
				Parameters.OnOutput = [](auto &Neighbours, auto &Label) {
					Label = 0;
					for (const auto &Neighbour : Neighbours)
					{
						Label += Neighbour.Prototype->Label;
					}
					Label *= (FReal) Neighbours.Size();
				};
			}


		protected:
			virtual FVoid _Initialize() override
			{
				State.Neighbours.Reserve(Parameters.KNearest);
				
				State.Neighbours.IterateAll();
				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Distance2 = TLimit<FReal>::Infinity();
					Neighbour.Prototype = NullPtr;
				}
				State.Neighbours.IterateAll(False);
			};

			virtual FVoid _Use(const typename FModel::FFeature &Feature, typename FModel::FLabel &Label, FBoolean bTraining) override
			{
				FReal Distance2;
				const FReal One = 1;
				
				if (bTraining) { return; }
				
				State.Neighbours.Reset();
				for (auto &Prototype : State.Prototypes)
				{
					Distance2 = Norm2(Prototype.Feature - Feature);
					if (Distance2 > State.Neighbours.Active().Distance2)
					{
						State.Neighbours.Swap({ Distance2, &Prototype });
					}
				}
				Parameters.OnOutput(State.Neighbours, Label);
			};

			virtual FVoid _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
			{
				State.Prototypes.Add(Sample);
			};


		};



	}



}