#include "pch.h"

#include "MLPrototyping.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"

using namespace MLPrototyping;

/*[&NN](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized) {}*/

FReturn main()
{
	const FSize Seed = 1;

	{
		using FLVQ = LVQ::TNN<2, 3>;
		
		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed);
	}

	{
		using FLVQ = LVQ::TLVQ1<2, 3>;
		
		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed);
	}

	return Success;
}