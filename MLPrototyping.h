#pragma once

#include "NDev.h"
#include "Generate.h"
#include "Window.h"

namespace MLPrototyping
{
	using namespace NDev;
	using namespace NDev::Types;

	namespace Measure
	{
		static const FSize Factor = 8;

		template<FSize SizeFeature, FSize SizeLabel>
		using TOnResults = TFunction<FVoid(const TData<typename TModel<SizeFeature, SizeLabel>::FError> &, const TData<typename TModel<SizeFeature, SizeLabel>::FSample> &, const TData<typename TModel<SizeFeature, SizeLabel>::FSample> &, const TData<typename TModel<SizeFeature, SizeLabel>::FSample> &, FBoolean)>;

		template<FSize SizeFeature, FSize SizeLabel>
		FVoid Uniform(TModel<SizeFeature, SizeLabel> &Model, TData<typename TModel<SizeFeature, SizeLabel>::FError> &Errors, FSize SeedIn = 0, TOnResults<SizeFeature, SizeLabel> OnResults = NullPtr, FSize Scale = 128, FReal Space = 1.5,  FBoolean bOptimize = False)
		{
			const FSize N = SizeFeature * Factor * Scale;

			using FModel = TModel<SizeFeature, SizeLabel>;
			using FParameters = TUniformDataParameters<SizeFeature, SizeLabel>;

			TUniform<FReal> Distribution;
			TSequence<FParameters> List(SizeLabel, True);
			TData<typename FModel::FSample> TSamples, VSamples, OSamples;
			FSize Index;
			
			Distribution.Parameters(-Space, Space);
			Distribution.Seed(SeedIn);
			Index = 0;
			for (auto &Item : List)
			{
				Item.N = N / SizeLabel;
				Item.N = N / SizeLabel;
				Item.Label = 0;
				Item.Label[Index] = 1;
				Item.Norm = 1;
				Item.Radius = 2.0 * (Index + 1.0) / (SizeLabel + 1.0);
				Distribution(Item.Mean);
				++Index;
			}

			Generate(TSamples, List);
			Generate(VSamples, List);
			Generate(OSamples, List);

			if (!Model.Initialized()) { Model.Initialize(); }
			Model.Train(TSamples);
			if (bOptimize) { Model.Optimize(OSamples); }
			Model.Validate(VSamples, Errors);

			if (OnResults) OnResults(Errors, TSamples, OSamples, VSamples, bOptimize);
		}

		template<FSize SizeFeature, FSize SizeLabel>
		FVoid Ring(TModel<SizeFeature, SizeLabel> &Model, TData<typename TModel<SizeFeature, SizeLabel>::FError> &Errors, FSize SeedIn = 0, TOnResults<SizeFeature, SizeLabel> OnResults = NullPtr, FSize Scale = 128, FReal Space = 1.5, FBoolean bOptimize = False)
		{
			const FSize N = SizeFeature * Factor * Scale;

			using FModel = TModel<SizeFeature, SizeLabel>;
			using FParameters = TRingDataParameters<SizeFeature, SizeLabel>;

			TUniform<FReal> Distribution;
			TSequence<FParameters> List(SizeLabel, True);
			TData<typename FModel::FSample> TSamples, VSamples, OSamples;
			FSize Index;

			Distribution.Parameters(-Space, Space);
			Distribution.Seed(SeedIn);
			Index = 0;
			for (auto &Item : List)
			{
				Item.N = N / SizeLabel;
				Item.Label = 0;
				Item.Label[Index] = 1;
				Item.Norm = 1;
				Item.Radius = (Index + 1.0) / (SizeLabel + 1.0);
				Item.SD = Item.Radius * (1.0 / 4.0);
				Distribution(Item.Mean);
				++Index;
			}

			Generate(TSamples, List);
			Generate(VSamples, List);
			Generate(OSamples, List);

			if (!Model.Initialized()) { Model.Initialize(); }
			Model.Train(TSamples);
			if (bOptimize) { Model.Optimize(OSamples); }
			Model.Validate(VSamples, Errors);

			if (OnResults) OnResults(Errors, TSamples, OSamples, VSamples, bOptimize);
		}

		template<FSize SizeFeature, FSize SizeLabel>
		FVoid Gamma(TModel<SizeFeature, SizeLabel> &Model, TData<typename TModel<SizeFeature, SizeLabel>::FError> &Errors, FSize SeedIn = 0, TOnResults<SizeFeature, SizeLabel> OnResults = NullPtr, FSize Scale = 128, FReal Space = 1.5, FBoolean bOptimize = False)
		{
			const FSize N = SizeFeature * Factor * Scale;

			using FModel = TModel<SizeFeature, SizeLabel>;
			using FParameters = TGammaDataParameters<SizeFeature, SizeLabel>;

			TUniform<FReal> Distribution;
			TSequence<FParameters> List(SizeLabel, True);
			TData<typename FModel::FSample> TSamples, VSamples, OSamples;
			FSize Index;

			Distribution.Parameters(-Space, Space);
			Distribution.Seed(SeedIn);
			Index = 0;
			for (auto &Item : List)
			{
				Item.N = N / SizeLabel;
				Item.Label = 0;
				Item.Label[Index] = 1;
				Item.Norm = 1;
				Item.Along = 1;
				Item.Beta = ((Index + 1.0) / (SizeLabel + 1.0)) * 1.5;
				Item.Alpha = ((Index + 1.0) / (SizeLabel + 1.0)) * 2;
				Distribution(Item.Mean);
				++Index;
			}

			Generate(TSamples, List);
			Generate(VSamples, List);
			Generate(OSamples, List);

			if (!Model.Initialized()) { Model.Initialize(); }
			Model.Train(TSamples);
			if (bOptimize) { Model.Optimize(OSamples); }
			Model.Validate(VSamples, Errors);

			if (OnResults) OnResults(Errors, TSamples, OSamples, VSamples, bOptimize);
		}

		template<FSize SizeFeature, FSize SizeLabel>
		FVoid Normal(TModel<SizeFeature, SizeLabel> &Model, TData<typename TModel<SizeFeature, SizeLabel>::FError> &Errors, FSize SeedIn = 0, TOnResults<SizeFeature, SizeLabel> OnResults = NullPtr, FSize Scale = 128, FReal Space = 1.5, FBoolean bOptimize = False)
		{
			const FSize N = SizeFeature * Factor * Scale;

			using FModel = TModel<SizeFeature, SizeLabel>;
			using FParameters = TNormalDataParameters<SizeFeature, SizeLabel>;

			TUniform<FReal> Distribution;
			TSequence<FParameters> List(SizeLabel, True);
			TData<typename FModel::FSample> TSamples, VSamples, OSamples;
			FSize Index;

			Distribution.Parameters(-Space, Space);
			Distribution.Seed(SeedIn);
			Index = 0;
			for (auto &Item : List)
			{
				Item.N = N / SizeLabel;
				Item.Label = 0;
				Item.Label[Index] = 1;
				Item.Norm = 1;
				Item.SD = (Index + 1.0) / (SizeLabel + 1.0);
				Distribution(Item.Mean);
				++Index;
			}

			Generate(TSamples, List, SeedIn);
			Generate(VSamples, List, SeedIn ? SeedIn + 1 : 0);
			Generate(OSamples, List, SeedIn ? SeedIn + 2 : 0);
			
			if (!Model.Initialized()) { Model.Initialize(); }
			Model.Train(TSamples);
			if (bOptimize) { Model.Optimize(OSamples); }
			Model.Validate(VSamples, Errors);

			if (OnResults) OnResults(Errors, TSamples, OSamples, VSamples, bOptimize);
		}



	};

	template<FSize SizeFeature, FSize SizeLabel, typename TypeModel>
	Measure::TOnResults<SizeFeature, SizeLabel> OnResults(FWindow &WindowData, FWindow &WindowError, TypeModel &Model)
	{
		return [&Model, &WindowData, &WindowError](const auto &Errors, const auto &TSamples, const auto &OSamples, const auto &VSamples, auto bOptimized) {
			auto EMeta = FWindow::FMeta::Default();
			EMeta.Name = Text("Error"); EMeta.Type = FWindow::FMeta::EType::Line;
			FWindow::Display<SizeFeature, SizeLabel>(Errors, WindowError, EMeta);
			
			auto bHold = WindowData.bHold; WindowData.bHold = True;
			
			auto VMeta = FWindow::FMeta::Default();
			VMeta.Name = Text("Validate");
			FWindow::Display<SizeFeature, SizeLabel>(VSamples, WindowData, VMeta);

			auto TMeta = FWindow::FMeta::Default();
			TMeta.Name = Text("Train");
			FWindow::Display<SizeFeature, SizeLabel>(TSamples, WindowData, TMeta);

			TData<TypeModel::FPrototype> PSamples;
			PSamples.Data(Model.State.Prototypes.Descriptor(), True);
			auto PMeta = FWindow::FMeta::Default();
			PMeta.Name = Text("Prototype"); PMeta.Size = 8.0; PMeta.Opacity = 0.5;
			FWindow::Display<SizeFeature, SizeLabel>(PSamples, WindowData, PMeta);
			
			WindowData.bHold = bHold;
		};
	}

	
}