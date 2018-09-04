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


	private:
		CMLPrototyping();

		static CMLPrototyping* _Instance;


	};



}