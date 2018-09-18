#pragma once

#include "MLPrototyping_Configurations.h"

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