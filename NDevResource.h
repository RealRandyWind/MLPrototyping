#pragma once

#include "MLPrototyping_Configurations.h"

#include "NDevTypes.h"
#include "NDevSequence.h"

namespace NDev
{
	using namespace Types;

	class MLPrototyping_Exports CResource;
	
	struct MLPrototyping_Exports _FResource
	{
		FSize Id;
		CResource *Pointer;
	};

	template struct MLPrototyping_Exports TSequence<_FResource>;

	class MLPrototyping_Exports CResource
	{
	public:
		CResource();

		~CResource();

		FSize Id();

		const FSize Id() const;

		static CResource &Reference(FSize);

		static CResource *Pointer(FSize);

		static FSize ResourceCount();

		static FSize ResourceBufferSize();


	private:
		FSize _Id;

		static FSize _NextId;
		static FSize _Count;
		static TSequence<_FResource> _List;


	};



}