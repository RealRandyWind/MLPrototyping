#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "Point.h"
#include "Data.h"
#include "Model.h"
#include "Sequence.h"

namespace MLPrototyping
{
	template<FSize SizeFeature, FSize SizeLabel>
	struct TUniformDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		FSize N;
		FReal Norm, Radius;
		FFeature Mean;
		FLabel Label;

		static TUniformDataParameters<SizeFeature, SizeLabel> Default()
		{
			TUniformDataParameters<SizeFeature, SizeLabel> Item;
			Item.N = 1024;
			Item.Norm = 1;
			Item.Radius = 1;
			Item.Mean = 0;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	template<FSize SizeFeature, FSize SizeLabel>
	struct TNormalDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		FSize N;
		FReal SD, Norm;
		FFeature Mean;
		FLabel Label;

		static TNormalDataParameters<SizeFeature, SizeLabel> Default()
		{
			TNormalDataParameters<SizeFeature, SizeLabel> Item;
			Item.N = 1024;
			Item.SD = 1;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	template<FSize SizeFeature, FSize SizeLabel>
	struct TGammaDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		FSize N;
		FReal Alpha, Beta, Norm;
		FFeature Mean, Along;
		FLabel Label;

		static TGammaDataParameters<SizeFeature, SizeLabel> Default()
		{
			TGammaDataParameters<SizeFeature, SizeLabel> Item;
			Item.N = 1024;
			Item.Alpha = 1.5;
			Item.Beta = 2;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Along = 0;
			Item.Along[0] = 1;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	template<FSize SizeFeature, FSize SizeLabel>
	struct TRingDataParameters
	{
		using FModel = TModel<SizeFeature, SizeLabel>;

		using FFeature = typename FModel::FFeature;

		using FLabel = typename FModel::FLabel;

		using FSample = typename FModel::FSample;

		FSize N;
		FReal SD, Readius, Norm;
		FFeature Mean;
		FLabel Label;

		static TRingDataParameters<SizeFeature, SizeLabel> Default()
		{
			TRingDataParameters<SizeFeature, SizeLabel> Item;
			Item.N = 1024;
			Item.SD = .5;
			Item.Norm = 1;
			Item.Mean = 0;
			Item.Readius = 1;
			Item.Label = 0;
			Item.Label[0] = 1;
			return Item;
		}
	};

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TUniformDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TUniformDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TUniformDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TUniformDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TSequence<TUniformDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		const FReal Zero = 0;
		FSize Index, End = 0, Offset = 0, N = 0;
		TUniform<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

		for (const auto &Parameters : List)
		{
			Distribution.Parameters(-Parameters.Radius, Parameters.Radius);
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

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TUniformDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TUniformDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TUniformDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TUniformDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TSequence<TUniformDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		const FReal Zero = 0;
		FSize Index, End = 0, Offset = 0, N = 0;
		TUniform<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

		for (const auto &Parameters : List)
		{
			Distribution.Parameters(-Parameters.Radius, Parameters.Radius);
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

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TNormalDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TNormalDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TNormalDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TNormalDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TSequence<TNormalDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		const FReal Zero = 0;
		FSize Index, End = 0, Offset = 0, N = 0;
		TNormal<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

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

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TNormalDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TNormalDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TNormalDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TNormalDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TSequence<TNormalDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		const FReal Zero = 0;
		FSize Index, End = 0, Offset = 0, N = 0;
		TNormal<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

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
				Sample.Feature *= Parameters.Norm;
				Sample.Feature += Parameters.Mean;
			}
		}
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TGammaDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TGammaDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TGammaDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TGammaDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TSequence<TGammaDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		FSize Index, End = 0, Offset = 0, N = 0;
		TGamma<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

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

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TGammaDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TGammaDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TGammaDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TGammaDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TSequence<TGammaDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		FSize Index, End = 0, Offset = 0, N = 0;
		TGamma<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

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

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TRingDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TRingDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TRingDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TRingDataParameters<SizeFeature, SizeLabel>::FFeature> &Data, TSequence<TRingDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		const FReal Zero = 0;
		FSize Index, End = 0, Offset = 0, N = 0;
		typename TRingDataParameters<SizeFeature, SizeLabel>::FFeature Unit;
		TNormal<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

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

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TRingDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TRingDataParameters<SizeFeature, SizeLabel> &Parameters, FSize Seed = 0)
	{
		TSequence<TRingDataParameters<SizeFeature, SizeLabel>> List;

		List.Data(&Parameters, 1, 1, False);
		ModelData(Data, List, Seed);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	static FVoid ModelData(TData<typename TRingDataParameters<SizeFeature, SizeLabel>::FSample> &Data, TSequence<TRingDataParameters<SizeFeature, SizeLabel>> &List, FSize Seed = 0)
	{
		const FReal Zero = 0;
		FSize Index, End = 0, Offset = 0, N = 0;
		typename TRingDataParameters<SizeFeature, SizeLabel>::FFeature Unit;
		TNormal<FReal> Distribution;
		Distribution.Seed(Seed);

		for (const auto &Parameters : List) { N += Parameters.N; }
		Data.Reserve(N, True);

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



}