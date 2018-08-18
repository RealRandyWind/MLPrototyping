// MLPrototyping.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MLPrototyping.h"
#include "MLPrototyping_Math.h"
#include <random>


using namespace MLPrototyping;

CMLPrototyping* CMLPrototyping::Instance = nullptr;

CMLPrototyping::CMLPrototyping()
{

}

CMLPrototyping::~CMLPrototyping()
{

}

CMLPrototyping* CMLPrototyping::GetInstance()
{
	if (!Instance) { Instance = new CMLPrototyping(); }
	return Instance;
}

void CMLPrototyping::ModelData(TData<FNormalDataParameters::FPoint> &Data, FNormalDataParameters &Parameters, size_t Seed)
{
	TSequence<FNormalDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FNormalDataParameters::FPoint> &Data, TSequence<FNormalDataParameters> &List, size_t Seed)
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

void CMLPrototyping::ModelData(TData<FGammaDataParameters::FPoint> &Data, FGammaDataParameters &Parameters, size_t Seed)
{
	TSequence<FGammaDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FGammaDataParameters::FPoint> &Data, TSequence<FGammaDataParameters> &List, size_t Seed)
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
			auto &Point = Data[Offset + Index];
			Distribution(Point);
			Point *= Parameters.Norm;
			Point += Parameters.Mean;
		}
	}
}

void CMLPrototyping::ModelData(TData<FRingDataParameters::FPoint> &Data, FRingDataParameters &Parameters, size_t Seed)
{
	TSequence<FRingDataParameters> List;

	List.Data(&Parameters, 1, 1, false);
	ModelData(Data, List, Seed);
}

void CMLPrototyping::ModelData(TData<FRingDataParameters::FPoint> &Data, TSequence<FRingDataParameters> &List, size_t Seed)
{
	const real_t Zero = 0;
	size_t Index, End = 0, Offset = 0, N = 0;
	FRingDataParameters::FPoint Unit;
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
			Distribution(Unit);
			Normalize(Unit);
			Unit *= Parameters.Readius;
			Point *= Parameters.Norm;
			Point += Parameters.Mean + Unit;
		}
	}
}