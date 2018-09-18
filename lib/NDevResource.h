#pragma once

#include "NDevTypes.h"
#include "NDevSequence.h"

namespace NDev
{
	using namespace Types;

	class CResource;
	
	struct _FResource
	{
		FSize Id;
		CResource *Pointer;
	};

	class CResource
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