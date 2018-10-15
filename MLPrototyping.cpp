#include "pch.h"

#include "MLPrototyping.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"
#include "Window.h"

#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtCharts/QtCharts>
#include <QtCore/QtCore>

using namespace MLPrototyping;

const FSize Seed = 1;
const FSize F = 2, L = 3;

/*[&NN](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized) {}*/

FReturn main(int argc, char** argv)
{
	/* Case Nearest Neighbour (NN) */
	{
		using FLVQ = LVQ::TNN<F, L>;
		
		auto WindowData = FWindow::Default();

		WindowData.Title = Text("Case Nearest Neighbour (NN) - Data");
		
		WindowData.bWait = WindowData.bHold = True;

		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed, [&Model, &WindowData](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized) {
			auto VMeta = FWindow::FMeta::Default();
			VMeta.Name = Text("Validate");
			FWindow::Display<F, L>(VSamples, WindowData, VMeta);

			auto TMeta = FWindow::FMeta::Default();
			TMeta.Name = Text("Train");
			FWindow::Display<F, L>(TSamples, WindowData, TMeta);

			auto PMeta = FWindow::FMeta::Default();
			PMeta.Name = Text("Prototype"); PMeta.Size = 8.0; PMeta.Opacity = 0.3;
			FWindow::Display<F, L>(TSamples, WindowData, PMeta);
		});
	}

	/* Case Learning Vector Quantization One (LVQ1) */
	{
		using FLVQ = LVQ::TLVQ1<F, L>;
		auto Window = FWindow::Default();
		
		TData<FLVQ::FError> Errors;
		FLVQ Model;
		Model.UseDefaultParameters();
		Model.Initialize();
		Measure::Normal(Model, Errors, Seed);
	}

	/* Case Split Merge Dynamic Learning Vector Quantization (SMDLVQ) */
	{
		using FLVQ = LVQ::TSMDLVQ<F, L>;
		auto Window = FWindow::Default();

	}

	return Success;
}