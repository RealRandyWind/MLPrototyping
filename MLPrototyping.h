#pragma once

#ifdef MLPrototyping_Exports
#define MLPrototyping_Exports __declspec(dllexport)
#else
#define MLPrototyping_Exports __declspec(dllimport)
#endif

namespace MLPrototyping
{
	class MLPrototyping_Exports CMLPrototyping final
	{
	public:
		~CMLPrototyping();
		static CMLPrototyping* GetInstance();

	private:
		CMLPrototyping();
		static CMLPrototyping* Instance;
	};
}