#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "Model.h"
#include "Sequence.h"

namespace MLPrototyping
{
	namespace LVQ
	{
		template<size_t SizeFeature, size_t SizeLabel>
		struct TLVQ1 : public TModel<SizeFeature, SizeLabel>
		{
			using FModel = TModel<SizeFeature, SizeLabel>;

			using FPrototype = typename FModel::FSample;

			struct FParameters
			{
				real_t LearningRate;
				size_t KNearest, NPrototypes;
			};

			struct FNeighbour
			{
				real_t Distance2;
				typename FModel::FFeature Direction;
				FPrototype *Prototype;
			};

			struct FState
			{
				TSequence<FPrototype> Prototypes;
				TSequence<FNeighbour> Neighbours;
			};

			FParameters Parameters;
			FState State;


		protected:
			virtual void_t _Initialize() override
			{
				if (Parameters.KNearest > Parameters.NPrototypes) { return;  }

				State.Prototypes.Reserve(Parameters.NPrototypes, true);
				State.Neighbours.Reserve(Parameters.KNearest, true);
				
				for (auto &Prototype : State.Prototypes)
				{
					Prototype.Label = 0;
					Prototype.Feature = 0;
				}
				
				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Distance2 = TLimit<real_t>::Infinity();
					Neighbour.Direction = 0;
					Neighbour.Prototype = nullptr;
				}
			}

			virtual void_t _Use(const typename FModel::FFeature &Feature, typename FModel::FLabel &Label, bool_t bTraining) override
			{
				real_t Distance2;
				typename FModel::FFeature Direction;
				const real_t One = 1;
				const real_t OneByKNearest = One / Parameters.KNearest;
				
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

				Label = 0;
				for (const auto &Neighbour : State.Neighbours)
				{
					Label += Neighbour.Prototype->Label;
				}
				Label *= OneByKNearest;
			}

			virtual void_t _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
			{
				const real_t One = 1;
				const real_t LearningRate = Parameters.LearningRate;
				const typename FModel::FLabel Error = One - (Sample.Label - Label);
				const real_t Delta = Norm(Error);

				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Prototype->Feature += Delta * Neighbour.Direction;
				}
			}


		};



	}



}