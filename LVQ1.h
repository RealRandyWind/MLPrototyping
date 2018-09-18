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
		struct TLVQ1 : public TModel<SizeFeature, SizeLabel>
		{
			using FModel = TModel<SizeFeature, SizeLabel>;

			using FPrototype = typename FModel::FSample;

			struct FNeighbour
			{
				FReal Distance2;
				typename FModel::FFeature Direction;
				FPrototype *Prototype;
			};

			using FOnOutput = std::function<void(TSequence<FNeighbour>&, typename FModel::FLabel&)>;

			struct FParameters
			{
				FReal LearningRate;
				FSize KNearest, NPrototypes;
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
				Parameters.KNearest = 1;
				Parameters.NPrototypes = 3;
				Parameters.LearningRate = 0.01;
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
				if (Parameters.KNearest > Parameters.NPrototypes) { return;  }

				State.Prototypes.Reserve(Parameters.NPrototypes, True);
				State.Neighbours.Reserve(Parameters.KNearest, True);
				
				for (auto &Prototype : State.Prototypes)
				{
					Prototype.Label = 0;
					Prototype.Label[0] = 1;
					Prototype.Feature = 0;
				}
				
				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Distance2 = TLimit<FReal>::Infinity();
					Neighbour.Direction = 0;
					Neighbour.Prototype = NullPtr;
				}
			}

			virtual FVoid _Use(const typename FModel::FFeature &Feature, typename FModel::FLabel &Label, FBoolean bTraining) override
			{
				FReal Distance2;
				typename FModel::FFeature Direction;
				const FReal One = 1;
				
				State.Neighbours.Reset();
				for (auto &Prototype : State.Prototypes)
				{
					Direction = Prototype.Feature - Feature;
					Distance2 = Norm2(Direction);

					if (Distance2 > State.Neighbours.Active().Distance2)
					{
						State.Neighbours.Swap({ Distance2, Direction, &Prototype });
					}
				}
				Parameters.OnOutput(State.Neighbours, Label);
			}

			virtual FVoid _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
			{
				const FReal One = 1;
				const FReal LearningRate = Parameters.LearningRate;
				const typename FModel::FLabel Error = One - (Sample.Label - Label);
				const FReal Delta = Norm(Error) * LearningRate;

				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Prototype->Feature += Delta * Neighbour.Direction;
				}
			}


		};



	}



}