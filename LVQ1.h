#pragma once

#include "NDev.h"

namespace MLPrototyping
{
	namespace LVQ
	{
		using namespace NDev;
		using namespace NDev::Types;

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

			struct FParameters
			{
				using FOnOutput = TFunction<FVoid(TSequence<FNeighbour> &, typename FModel::FLabel &)>;

				using FOnWeight = TFunction<FReal(const FNeighbour &)>;

				FReal LearningRate, DomainSD;
				FSize KNearest, NPrototypes, Seed;
				typename FModel::FFeature DomainOrigin;
				FOnOutput OnOutput;
				FOnWeight OnWeight;
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
				Parameters.Seed = 0;
				Parameters.KNearest = 1;
				Parameters.NPrototypes = 3;
				Parameters.LearningRate = 0.01;
				Parameters.DomainSD = 1;
				Parameters.DomainOrigin = 0;
				Parameters.OnOutput = [](auto &Neighbours, auto &Label) {
					Label = 0;
					for (const auto &Neighbour : Neighbours)
					{
						Label += Neighbour.Prototype->Label;
					}
					Label *= (FReal) Neighbours.Size();
				};
				Parameters.OnWeight = NullPtr;
			}


		protected:
			virtual FVoid _Initialize() override
			{
				FSize LabelIndex = 0;
				TNormal<FReal> Distribution;

				if (Parameters.KNearest > Parameters.NPrototypes) { exit(Failure);  }
				if (SizeLabel > Parameters.NPrototypes) { exit(Failure); }

				State.Prototypes.Reserve(Parameters.NPrototypes, True);
				State.Neighbours.Reserve(Parameters.KNearest, True);
				
				Distribution.Seed(Parameters.Seed);
				Distribution.Parameters(0, Parameters.DomainSD);
				
				for (auto &Prototype : State.Prototypes)
				{
					Prototype.Label = 0;
					Prototype.Label[LabelIndex % SizeLabel] = 1;
					Distribution(Prototype.Feature);
					Prototype.Feature += Parameters.DomainOrigin;
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
				if (OnUseNeighbours) { OnUseNeighbours(State.Neighbours); }
				Parameters.OnOutput(State.Neighbours, Label);
			}

			virtual FVoid _Train(const typename FModel::FLabel &Label, const typename FModel::FSample &Sample) override
			{
				const FReal One = 1;
				const FReal LearningRate = Parameters.LearningRate;
				const typename FModel::FLabel Error = One - (Sample.Label - Label);
				const FReal Delta = Norm(Error) * LearningRate;
				FReal Weight;

				for (auto &Neighbour : State.Neighbours)
				{
					Weight = Parameters.OnWeight ? Parameters.OnWeight(Neighbour) : One;
					Neighbour.Prototype->Feature += Delta * Weight * Neighbour.Direction;
				}
				if (OnTrainPrototypes) { OnTrainPrototypes(State.Prototypes); }
			}


		};



	}



}