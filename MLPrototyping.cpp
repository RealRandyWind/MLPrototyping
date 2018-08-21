// MLPrototyping.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MLPrototyping.h"
#include "MLPrototyping_Math.h"
#include <random>


using namespace MLPrototyping;

CMLPrototyping* CMLPrototyping::_Instance = nullptr;

CMLPrototyping::CMLPrototyping()
{

}

CMLPrototyping::~CMLPrototyping()
{
	
}

CMLPrototyping* CMLPrototyping::Instance()
{
	if (!_Instance) { _Instance = new CMLPrototyping(); }
	return _Instance;
}

/* Normal Data */

void CMLPrototyping::ModelData(TData<FNormalDataParameters::FFeature> &Data, FNormalDataParameters &Parameters, size_t Seed)
{
	TSequence<FNormalDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FNormalDataParameters::FFeature> &Data, TSequence<FNormalDataParameters> &List, size_t Seed)
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

void CMLPrototyping::ModelData(TData<FNormalDataParameters::FSample> &Data, FNormalDataParameters &Parameters, size_t Seed)
{
	TSequence<FNormalDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FNormalDataParameters::FSample> &Data, TSequence<FNormalDataParameters> &List, size_t Seed)
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
			auto &Sample = Data[Offset + Index];
			Sample.Label = Parameters.Label;
			Distribution(Sample.Feature);
			Sample.Feature *= Parameters.Norm;
			Sample.Feature += Parameters.Mean;
		}
	}
}

/* Gamma Data */

void CMLPrototyping::ModelData(TData<FGammaDataParameters::FFeature> &Data, FGammaDataParameters &Parameters, size_t Seed)
{
	TSequence<FGammaDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FGammaDataParameters::FFeature> &Data, TSequence<FGammaDataParameters> &List, size_t Seed)
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

void CMLPrototyping::ModelData(TData<FGammaDataParameters::FSample> &Data, FGammaDataParameters &Parameters, size_t Seed)
{
	TSequence<FGammaDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FGammaDataParameters::FSample> &Data, TSequence<FGammaDataParameters> &List, size_t Seed)
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

/* Ring Data */

void CMLPrototyping::ModelData(TData<FRingDataParameters::FFeature> &Data, FRingDataParameters &Parameters, size_t Seed)
{
	TSequence<FRingDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FRingDataParameters::FFeature> &Data, TSequence<FRingDataParameters> &List, size_t Seed)
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

void CMLPrototyping::ModelData(TData<FRingDataParameters::FSample> &Data, FRingDataParameters &Parameters, size_t Seed)
{
	TSequence<FRingDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FRingDataParameters::FSample> &Data, TSequence<FRingDataParameters> &List, size_t Seed)
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