#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "MLPrototyping_Math.h"
#include "Resource.h"
#include "Point.h"
#include "Data.h"

namespace MLPrototyping
{
	template<size_t SizeFeature, size_t SizeLabel>
	struct TModel : public CResource
	{
		using FFeature = TPoint<SizeFeature, real_t>;

		using FLabel = TPoint<SizeLabel, real_t>;

		struct FSample
		{
			FFeature Feature;
			FLabel Label;
		};

		struct FError
		{
			FLabel Value, Label;
			real_t Weight, Epsilon;
			size_t WorkerID, Significance;
			duration_t Time;
		};

		bool_t _bInitialized;

		TModel()
		{
			_bInitialized = false;
		}

		~TModel() { }

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

		void Train(const TData<FSample> &Samples)
		{
			FLabel Label;

			if (!_bInitialized) { return; }

			for (const auto &Sample : Samples)
			{
				_Use(Sample.Feature, Label);
				_Train(Label, Sample);
			}
		}

		void Use(const TData<FFeature> &Features, TData<FLabel> &Labels)
		{
			size_t Index, End;

			if (!_bInitialized) { return; }

			End = Features.Size();
			Labels.Reserve(End, true);
			for (Index = 0; Index < End; ++Index)
			{
				_Use(Features[Index], Labels[Index]);
			}
		}

		void Validate(const TData<FSample> &Samples, TData<FError> &Errors)
		{
			time_t Start;
			size_t Index, End;

			if (!_bInitialized) { return; }


			End = Samples.Size();
			Errors.Reserve(End, true);
			for (Index = 0; Index < End; ++Index)
			{
				const auto &Sample = Samples[Index];
				auto &Error = Errors[Index];
				Start = clock_t::now();
				_Use(Sample.Feature, Error.Label);
				Error.Time = (clock_t::now() - Start);
				_Validate(Sample, Error);
			}
		}

		void Optimize(const TData<FSample> &Samples)
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

		virtual void _Train(const FLabel &, const FSample &) = 0;

		virtual void _Optimize(const FSample &) { }

		virtual void _Optimize() { }

		virtual void _Validate(const FSample &Sample, FError &Error)
		{
			Error.Value = Sample.Label - Error.Label;
			Error.Weight = 1;
			Error.WorkerID = 1; 
			Error.Epsilon = TLimit<real_t>::Epsilon();
			Error.Significance = TLimit<size_t>::Infinity();
		}


	};



}