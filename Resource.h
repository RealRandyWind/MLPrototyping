#pragma once

#ifdef MLPrototyping_Exports
#define MLPrototyping_Exports __declspec(dllexport)
#else
#define MLPrototyping_Exports __declspec(dllimport)
#endif

#include "MLPrototyping_Types.h"
#include "Sequence.h"

namespace MLPrototyping
{
	class MLPrototyping_Exports CResource;
	
	struct MLPrototyping_Exports _FResource
	{
		size_t Id;
		CResource *Pointer;
	};

	template struct MLPrototyping_Exports TSequence<_FResource>;

	class MLPrototyping_Exports CResource
	{
	public:
		CResource();

		~CResource();

		size_t Id();

		const size_t Id() const;

		static CResource &Reference(size_t);

		static CResource *Pointer(size_t);

		static size_t ResourceCount();

		static size_t ResourceBufferSize();


	private:
		size_t _Id;

		static size_t _NextId;
		static size_t _Count;
		static TSequence<_FResource> _List;


	};


}