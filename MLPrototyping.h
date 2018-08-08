#pragma once

#ifdef MLPROTOTYPING_EXPORTS
#define MLPROTOTYPING_EXPORTS __declspec(dllexport)
#else
#define MLPROTOTYPING_EXPORTS __declspec(dllimport)
#endif

namespace MLPrototyping
{
	class MLPROTOTYPING_EXPORTS CMLPrototyping final
	{
	public:
		~CMLPrototyping();
		static CMLPrototyping* GetInstance();

	private:
		CMLPrototyping();
		static CMLPrototyping* Instance;
	};
}