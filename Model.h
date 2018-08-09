#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "Point.h"
#include "Data.h"

namespace MLPrototyping
{
	template<size_t SizeFeature, size_t SizeLabel>
	struct TModel
	{
		using FFeature = TPoint<SizeFeature, real_t>;

		using FLabel = TPoint<SizeLabel, real_t>;

		struct FSample
		{
			FFeature Feature;
			FLabel Label;
		};

		struct FPerformence
		{
			FLabel ErrorMin, ErrorMax, ErrorMean, ErrorSD, ErrorSkew;
			size_t ComplexOperations, SimpleOperations, MemoryReads, MemoryWrites;
			size_t N, NThreads;
			duration_t RunningTime;
		};


		size_t FeatureSize()
		{
			return SizeFeature;
		}

		size_t LabelSize()
		{
			return SizeLabel;
		}

		void Initialize()
		{
			_Initialize();
		}

		void Train(TData<FSample> &Samples)
		{
			FLabel Label;

			for (const auto &Sample : Samples)
			{
				_Use(Sample.Feature, Label);
				_Train(Label, Sample.Label);
			}
		}

		void Use(TData<FFeature> &Features, TData<FLabel> &Labels)
		{
			size_t Index, End;

			End = Features.Size();
			Labels._Size = End;
			Labels.Reserve(End);
			for (Index = 0; Index < End; ++Index)
			{
				_Use(Features[Index], Labels[Index]);
			}
		}

		void Validate(TData<FSample> &Samples, FPerformence &Performance)
		{
			FLabel Label;
			time_t Start;

			for (const auto &Sample : Samples)
			{
				Start = clock_t::now();
				_Use(Sample.Feature, Label);
				Performance.RunningTime += (clock_t::now() - Start);
				++Performance.N;
			}
		}

		void Optimize(TData<FSample> &Samples)
		{
			for (const auto &Sample : Samples)
			{
				_Optimize(Sample);
			}
		}

		void Optimize()
		{
			_Optimize();
		}


	protected:
		virtual void _Initialize() = 0;

		virtual void _Use(const FFeature &, FLabel &) = 0;

		virtual void _Train(const FLabel &, const FLabel &) = 0;

		virtual void _Optimize(const FSample &) = 0;

		virtual void _Optimize() = 0;


	};



}