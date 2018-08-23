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
			using FPrototype = FSample;

			struct FParameters
			{
				real_t LearningRate, GenerateSD;
				size_t KNearest, NPrototypes, GenerateSeed;
				FFeature GenerateMean;
			};

			struct FNeighbour
			{
				real_t Distance2;
				FFeature Direction;
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
			virtual void _Initialize() override
			{
				const real_t Zero = 0;
				TNormal<real_t> Distribution;
				
				if (Parameters.KNearest > Parameters.NPrototypes) { return;  }
				
				Distribution.Seed(Parameters.GenerateSeed);
				Distribution.Parameters(Zero, Parameters.GenerateSD);

				State.Prototypes.Reserve(Parameters.NPrototypes, true);
				State.Neighbours.Reserve(Parameters.KNearest, true);
				
				for (auto &Prototype : State.Prototypes)
				{
					Prototype.Label = 0;
					Distribution(Prototype.Feature);
				}
				
				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Distance2 = TLimit<real_t>::Infinity();
					Neighbour.Direction = 0;
					Neighbour.Prototype = nullptr;
				}
			}

			virtual void _Use(const FFeature &Feature, FLabel &Label) override
			{
				real_t Distance2;
				FFeature Direction;
				const real_t One = 1;
				const real_t OneByKNearest = One / Parameters.KNearest;

				for (auto &Prototype : State.Prototypes)
				{
					Direction = Prototype.Feature - Feature;
					Distance2 = Norm2(Direction);

					if (Distance2 > State.Neighbours.Active().Distance2)
					{
						State.Neighbours.Swap({ Distance2, Direction, &Prototype });
					}
				}

				Label = { 0 };
				for (const auto &Neighbour : State.Neighbours)
				{
					Label += Neighbour.Prototype->Label;
				}
				Label *= OneByKNearest;
			}

			virtual void _Train(const FLabel &Label, const FLabel &Target) override
			{
				const real_t One = 1;
				const real_t LearningRate = Parameters.LearningRate;
				const FLabel Error = One - (Target - Label);
				const real_t Delta = Norm(Error);

				for (auto &Neighbour : State.Neighbours)
				{
					Neighbour.Prototype->Feature += Delta * Neighbour.Direction;
				}
			}
		};
	}
}