#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "MLPrototyping_Math.h"
#include "Point.h"
#include "Data.h"

namespace MLPrototyping
{
	template<size_t SizeFeature, size_t SizeLabel>
	struct TModel
	{
		using FLimit = TLimit<real_t>;
		using FFeature = TPoint<SizeFeature, real_t>;

		using FLabel = TPoint<SizeLabel, real_t>;

		struct FSample
		{
			FFeature Feature;
			FLabel Label;
		};

		struct FPerformence
		{
			FLabel ErrorMin, ErrorMax, ErrorMean, ErrorSD, ErrorSkew, LabelScore;
			real_t ModelScore;
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

			Performance.ErrorMin = FLimit::Infinity();
			Performance.ErrorMax = -FLimit::Infinity();
			Performance.ErrorMean = 0;
			Performance.ErrorSD = 0;
			Performance.ErrorSkew = 0;
			Performance.LabelScore = 0;
			Performance.N = 0;
			Performance.NThreads = 0;
			Performance.RunningTime = duration_t();

			for (const auto &Sample : Samples)
			{
				Start = clock_t::now();
				_Use(Sample.Feature, Label);
				Performance.RunningTime += (clock_t::now() - Start);
				++Performance.N;
				_Validate(Label, Sample.Label, Performance);
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

		virtual void _Validate(const FLabel &Label, const FLabel &Target, FPerformence &Performence)
		{
			FLabel ErrorMean, ErrorSD, ErrorSkew;
			real_t N, K;

			N = static_cast<real_t>(Performence.N);
			K = static_cast<real_t>(Performence.N - 1);
			ErrorMean = Target - Label;
			ErrorSD = ErrorMean * ErrorMean;
			ErrorSkew = ErrorSD * ErrorMean;

			Performence.ErrorMean = ((Performence.ErrorMean / K) + ErrorMean) / N;
			Performence.ErrorSD = ((Performence.ErrorSD / K) + ErrorSD) / N;
			Performence.ErrorSkew = ((Performence.ErrorSD / K) + ErrorSkew) / N;
			Performence.ErrorMin = Min(ErrorMean, Performence.ErrorMin);
			Performence.ErrorMax = Max(ErrorMean, Performence.ErrorMax);
		}

	};



}