#pragma once

#include "MLPrototyping.h"
#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "MLPrototyping_Parameters.h"
#include "Data.h"
#include "Sequence.h"

namespace MLPrototyping
{
	template<size_t SizeFeature, size_t SizeLabel>
	struct TGenerate
	{
		using FNormal = typename TNormalDataParameters<SizeFeature, SizeLabel>;

		using FGamma = typename TGammaDataParameters<SizeFeature, SizeLabel>;

		using FRing = typename TRingDataParameters<SizeFeature, SizeLabel>;

		static void ModelData(TData<typename FNormal::FFeature> &Data, FNormal &Parameters, size_t Seed = 0)
		{
			TSequence<FNormal> List;

			List.Data(&Parameters, 1, 1, false);
			ModelData(Data, List, Seed);
		}

		static void ModelData(TData<typename FNormal::FFeature> &Data, TSequence<FNormal> &List, size_t Seed = 0)
		{
			const real_t Zero = 0;
			size_t Index, End = 0, Offset = 0, N = 0;
			TNormal<real_t> Distribution;
			Distribution.Seed(Seed);

			for (const auto &Parameters : List) { N += Parameters.N; }
			Data.Reserve(N, true);

			for (const auto &Parameters : List)
			{
				Distribution.Parameters(Zero, Parameters.SD);
				Offset += End;
				End = Parameters.N;
				for (Index = 0; Index < End; ++Index)
				{
					auto &Point = Data[Offset + Index];
					Distribution(Point);
					Point *= Parameters.Norm;
					Point += Parameters.Mean;
				}
			}
		}

		static void ModelData(TData<typename FNormal::FSample> &Data, FNormal &Parameters, size_t Seed = 0)
		{
			TSequence<FNormal> List;

			List.Data(&Parameters, 1, 1, false);
			ModelData(Data, List, Seed);
		}

		static void ModelData(TData<typename FNormal::FSample> &Data, TSequence<FNormal> &List, size_t Seed = 0)
		{
			const real_t Zero = 0;
			size_t Index, End = 0, Offset = 0, N = 0;
			TNormal<real_t> Distribution;
			Distribution.Seed(Seed);

			for (const auto &Parameters : List) { N += Parameters.N; }
			Data.Reserve(N, true);

			for (const auto &Parameters : List)
			{
				Distribution.Parameters(Zero, Parameters.SD);
				Offset += End;
				End = Parameters.N;
				for (Index = 0; Index < End; ++Index)
				{
					auto &Point = Data[Offset + Index];
					Distribution(Point);
					Point *= Parameters.Norm;
					Point += Parameters.Mean;
				}
			}
		}

		static void ModelData(TData<typename FGamma::FFeature> &Data, FGamma &Parameters, size_t Seed = 0)
		{
			TSequence<FGamma> List;

			List.Data(&Parameters, 1, 1, false);
			ModelData(Data, List, Seed);
		}

		static void ModelData(TData<typename FGamma::FFeature> &Data, TSequence<FGamma> &List, size_t Seed = 0)
		{
			size_t Index, End = 0, Offset = 0, N = 0;
			TGamma<real_t> Distribution;
			Distribution.Seed(Seed);

			for (const auto &Parameters : List) { N += Parameters.N; }
			Data.Reserve(N, true);

			for (const auto &Parameters : List)
			{
				Distribution.Parameters(Parameters.Alpha, Parameters.Beta);
				Offset += End;
				End = Parameters.N;
				for (Index = 0; Index < End; ++Index)
				{
					auto &Feature = Data[Offset + Index];
					Distribution(Feature);
					Feature *= Parameters.Norm;
					Feature += Parameters.Mean;
				}
			}
		}

		static void ModelData(TData<typename FGamma::FSample> &Data, FGamma &Parameters, size_t Seed = 0)
		{
			TSequence<FGamma> List;

			List.Data(&Parameters, 1, 1, false);
			ModelData(Data, List, Seed);
		}

		static void ModelData(TData<typename FGamma::FSample> &Data, TSequence<FGamma> &List, size_t Seed = 0)
		{
			size_t Index, End = 0, Offset = 0, N = 0;
			TGamma<real_t> Distribution;
			Distribution.Seed(Seed);

			for (const auto &Parameters : List) { N += Parameters.N; }
			Data.Reserve(N, true);

			for (const auto &Parameters : List)
			{
				Distribution.Parameters(Parameters.Alpha, Parameters.Beta);
				Offset += End;
				End = Parameters.N;
				for (Index = 0; Index < End; ++Index)
				{
					auto &Sample = Data[Offset + Index];
					Sample.Label = Parameters.Label;
					Distribution(Sample.Feature);
					Sample.Feature *= Parameters.Norm;
					Sample.Feature += Parameters.Mean;
				}
			}
		}

		static void ModelData(TData<typename FRing::FFeature> &Data, FRing &Parameters, size_t Seed = 0)
		{
			TSequence<FRing> List;

			List.Data(&Parameters, 1, 1, false);
			ModelData(Data, List, Seed);
		}

		static void ModelData(TData<typename FRing::FFeature> &Data, TSequence<FRing> &List, size_t Seed = 0)
		{
			const real_t Zero = 0;
			size_t Index, End = 0, Offset = 0, N = 0;
			FRingDataParameters::FFeature Unit;
			TNormal<real_t> Distribution;
			Distribution.Seed(Seed);

			for (const auto &Parameters : List) { N += Parameters.N; }
			Data.Reserve(N, true);

			for (const auto &Parameters : List)
			{
				Distribution.Parameters(Zero, Parameters.SD);
				Offset += End;
				End = Parameters.N;
				for (Index = 0; Index < End; ++Index)
				{
					auto &Feature = Data[Offset + Index];
					Distribution(Feature);
					Distribution(Unit);
					Normalize(Unit);
					Unit *= Parameters.Readius;
					Feature *= Parameters.Norm;
					Feature += Parameters.Mean + Unit;
				}
			}
		}

		static void ModelData(TData<typename FRing::FSample> &Data, FRing &Parameters, size_t Seed = 0)
		{
			TSequence<FRing> List;

			List.Data(&Parameters, 1, 1, false);
			ModelData(Data, List, Seed);
		}

		static void ModelData(TData<typename FRing::FSample> &Data, TSequence<FRing> &List, size_t Seed = 0)
		{
			const real_t Zero = 0;
			size_t Index, End = 0, Offset = 0, N = 0;
			FRingDataParameters::FFeature Unit;
			TNormal<real_t> Distribution;
			Distribution.Seed(Seed);

			for (const auto &Parameters : List) { N += Parameters.N; }
			Data.Reserve(N, true);

			for (const auto &Parameters : List)
			{
				Distribution.Parameters(Zero, Parameters.SD);
				Offset += End;
				End = Parameters.N;
				for (Index = 0; Index < End; ++Index)
				{
					auto &Sample = Data[Offset + Index];
					Sample.Label = Parameters.Label;
					Distribution(Sample.Feature);
					Distribution(Unit);
					Normalize(Unit);
					Unit *= Parameters.Readius;
					Sample.Feature *= Parameters.Norm;
					Sample.Feature += Parameters.Mean + Unit;
				}
			}
		}


	};



}