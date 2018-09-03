#pragma once

#include "MLPrototyping_Configurations.h"

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

		static CMLPrototyping* Instance();

		/* Normal Data */

		void_t ModelData(TData<FNormalDataParameters::FFeature> &, FNormalDataParameters &, size_t = 0);

		void_t ModelData(TData<FNormalDataParameters::FFeature> &, TSequence<FNormalDataParameters> &, size_t = 0);

		void_t ModelData(TData<FNormalDataParameters::FSample> &, FNormalDataParameters &, size_t = 0);

		void_t ModelData(TData<FNormalDataParameters::FSample> &, TSequence<FNormalDataParameters> &, size_t = 0);

		/* Gamma Data */

		void_t ModelData(TData<FGammaDataParameters::FFeature> &, FGammaDataParameters &, size_t = 0);

		void_t ModelData(TData<FGammaDataParameters::FFeature> &, TSequence<FGammaDataParameters> &, size_t = 0);

		void_t ModelData(TData<FGammaDataParameters::FSample> &, FGammaDataParameters &, size_t = 0);

		void_t ModelData(TData<FGammaDataParameters::FSample> &, TSequence<FGammaDataParameters> &, size_t = 0);

		/* Ring Data */

		void_t ModelData(TData<FRingDataParameters::FFeature> &, FRingDataParameters &, size_t = 0);

		void_t ModelData(TData<FRingDataParameters::FFeature> &, TSequence<FRingDataParameters> &, size_t = 0);

		void_t ModelData(TData<FRingDataParameters::FSample> &, FRingDataParameters &, size_t = 0);

		void_t ModelData(TData<FRingDataParameters::FSample> &, TSequence<FRingDataParameters> &, size_t = 0);


	private:
		CMLPrototyping();

		static CMLPrototyping* _Instance;


	};



}