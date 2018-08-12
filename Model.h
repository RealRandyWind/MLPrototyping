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

		bool_t _bInitialized;

		TModel()
		{
			_bInitialized = false;
		}

		~TModel()
		{

		}

		bool_t Initialized()
		{
			return _bInitialized;
		}

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
			_bInitialized = false;
			_Initialize();
			_bInitialized = true;
		}

		void Train(TData<FSample> &Samples)
		{
			FLabel Label;

			if (!_bInitialized) { return; }

			for (const auto &Sample : Samples)
			{
				_Use(Sample.Feature, Label);
				_Train(Label, Sample.Label);
			}
		}

		void Use(TData<FFeature> &Features, TData<FLabel> &Labels)
		{
			size_t Index, End;

			if (!_bInitialized) { return; }

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

			if (!_bInitialized) { return; }

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
			if (!_bInitialized) { return; }

			for (const auto &Sample : Samples)
			{
				_Optimize(Sample);
			}
		}

		void Optimize()
		{
			if (!_bInitialized) { return; }

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