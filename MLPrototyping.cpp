#include "pch.h"

#include "MLPrototyping.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"

using namespace MLPrototyping;

const FSize Seed = 1;
const FSize F = 2, L = 3;
const FReal SD = 1.0;

/*[&NN](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized) {}*/

FReturn main(int argc, char** argv)
{
	/* Case Nearest Neighbour (NN) */
	{
		using FLVQ = LVQ::TNN<F, L>;
		
		auto WindowData = FWindow::Default();
		WindowData.Title = Text("Case Nearest Neighbour (NN) - Data");
		auto WindowError = FWindow::Default();
		WindowError.Title = Text("Case Nearest Neighbour (NN) - Error");

		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed, OnResults<F, L>(WindowData, WindowError, Model));

		FWindow::Wait();
	}

	/* Case Learning Vector Quantization One (LVQ1) */
	{
		using FLVQ = LVQ::TLVQ1<F, L>;
		
		auto WindowData = FWindow::Default();
		WindowData.Title = Text("Case Learning Vector Quantization One (LVQ1) - Data");
		auto WindowError = FWindow::Default();
		WindowError.Title = Text("Case Learning Vector Quantization One (LVQ1) - Error");
		
		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed, OnResults<F, L>(WindowData, WindowError, Model));

		FWindow::Wait();
	}

	/* Case Split Merge Dynamic Learning Vector Quantization (SMDLVQ) */
	{
		using FLVQ = LVQ::TSMDLVQ<F, L>;
		
		auto WindowData = FWindow::Default();
		WindowData.Title = Text("Case Split Merge Dynamic Learning Vector Quantization (SMDLVQ) - Data");
		auto WindowError = FWindow::Default();
		WindowError.Title = Text("Case Split Merge Dynamic Learning Vector Quantization (SMDLVQ) - Error");

		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		//Measure::Normal(Model, Errors, Seed, OnResults<F, L>(WindowData, WindowError, Model));

		//FWindow::Wait();
	}

	return Success;
}