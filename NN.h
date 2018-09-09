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
		template<size_t SizeFeature, size_t SizeLabel>
		struct TNN : public TModel<SizeFeature, SizeLabel>
		{
			using FModel = TModel<SizeFeature, SizeLabel>;

			using FPrototype = typename FModel::FSample;

			struct FNeighbour
			{
				real_t Distance2;
				FPrototype *Prototype;
			};

			using FxOutput = std::function<void(TSequence<FNeighbour>&, typename FModel::FLabel&)>;

			struct FParameters
			{
				size_t KNearest;
				FxOutput OutputFunction;
			};

			struct FState
			{
				TSequence<FPrototype> Prototypes;
				TSequence<FNeighbour> Neighbours;
			};

			FParameters Parameters;
			FState State;

			void_t UseDefaultParameters()
			{
				Parameters.KNearest = 3;
				Parameters.OutputFunction = [](auto &Neighbours, auto &Label) {
					Label = 0;
					for (const auto &Neighbour : Neighbours)
					{
						Label += Neighbour.Prototype->Label;
					}
					Label *= (real_t) Neighbours.Size();
				};
			}


		protected:
			virtual void_t _Initialize() override
			{
				State.Neighbours.Reserve(Parameters.KNearest);
				
				State.Neighbours.IterateAll();
				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Distance2 = TLimit<real_t>::Infinity();
					Neighbour.Prototype = nullptr;
				}
				State.Neighbours.IterateAll(false);
			};

			virtual void_t _Use(const typename FModel::FFeature &Feature, typename FModel::FLabel &Label, bool_t bTraining) override
			{
				real_t Distance2;
				const real_t One = 1;
				
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
				Parameters.OutputFunction(State.Neighbours, Label);
			};

			virtual void_t _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
			{
				State.Prototypes.Add(Sample);
			};


		};



	}



}