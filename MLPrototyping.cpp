#include "pch.h"

#include "MLPrototyping.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"
#include "Window.h"

using namespace MLPrototyping;

/*[&NN](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized) {}*/

FReturn main()
{
	const FSize Seed = 1;

	/* Case Nearest Neighbour (NN) */
	{
		using FLVQ = LVQ::TNN<2, 3>;
		auto Window = FWindow::Default();

		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed, [&Model, &Window](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized){
			Window.bWait = Window.bHold = True;
			FWindow::Display(TSamples.Descriptor(), Window);
		});
	}

	/* Case Learning Vector Quantization One (LVQ1) */
	{
		using FLVQ = LVQ::TLVQ1<2, 3>;
		auto Window = FWindow::Default();
		
		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed);
	}

	/* Case Split Merge Dynamic Learning Vector Quantization (SMDLVQ) */
	{
		using FLVQ = LVQ::TSMDLVQ<2, 3>;
		auto Window = FWindow::Default();

	}

	return Success;
}