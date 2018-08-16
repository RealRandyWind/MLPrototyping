#pragma once

#ifdef MLPrototyping_Exports
#define MLPrototyping_Exports __declspec(dllexport)
#else
#define MLPrototyping_Exports __declspec(dllimport)
#endif

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Parameters.h"
#include "Data.h"
#include "Sequence.h"

namespace MLPrototyping
{
	class MLPrototyping_Exports CMLPrototyping final
	{
	public:
		~CMLPrototyping();

		static CMLPrototyping* GetInstance();

		void ModelData(TData<FNormalDataParameters::FPoint> &, FNormalDataParameters &, size_t = 0);

		void ModelData(TData<FNormalDataParameters::FPoint> &, TSequence<FNormalDataParameters> &, size_t = 0);

		void ModelData(TData<FGammaDataParameters::FPoint> &, FGammaDataParameters &, size_t = 0);

		void ModelData(TData<FGammaDataParameters::FPoint> &, TSequence<FGammaDataParameters> &, size_t = 0);

		void ModelData(TData<FHyperRingDataParameters::FPoint> &, FHyperRingDataParameters &, size_t = 0);

		void ModelData(TData<FHyperRingDataParameters::FPoint> &, TSequence<FHyperRingDataParameters> &, size_t = 0);


	private:
		CMLPrototyping();

		static CMLPrototyping* Instance;


	};



}