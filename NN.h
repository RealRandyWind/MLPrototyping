#pragma once

#include "NDev.h"

namespace MLPrototyping
{
	namespace LVQ
	{
		using namespace NDev;
		using namespace NDev::Types;

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

			struct FParameters
			{
				using FOnOutput = TFunction<FVoid(TSequence<FNeighbour>&, typename FModel::FLabel&)>;

				FSize KNearest;
				FOnOutput OnOutput;
			};

			struct FState
			{
				TSequence<FPrototype> Prototypes;
				TSequence<FNeighbour> Neighbours;
			};

			using FOnTrainPrototypes = TFunction<FVoid(const TSequence<FPrototype> &)>;

			using FOnUseNeighbours = TFunction<FVoid(const TSequence<FNeighbour> &)>;

			FOnTrainPrototypes OnTrainPrototypes;
			FOnUseNeighbours OnUseNeighbours;
			FParameters Parameters;
			FState State;

			FVoid UseDefaultParameters()
			{
				Parameters.KNearest = 3;
				Parameters.OnOutput = [](auto &Neighbours, auto &Label) {
					Label = 0;
					if (Neighbours.Empty()) { return; }
					for (const auto &Neighbour : Neighbours)
					{
						Label += Neighbour.Prototype->Label;
					}
					Label /= (FReal) Neighbours.Size();
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
				if (OnUseNeighbours) { OnUseNeighbours(State.Neighbours); }
				Parameters.OnOutput(State.Neighbours, Label);
			};

			virtual FVoid _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
			{
				State.Prototypes.Add(Sample);
				if (OnTrainPrototypes) { OnTrainPrototypes(State.Prototypes); }
			};


		};



	}



}