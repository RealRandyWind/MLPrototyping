#pragma once

#include "NDevTypes.h"
#include "NDevDefinitions.h"
#include "NDevPoint.h"
#include "NDevSequence.h"
#include "NDevMathAliases.h"

namespace MLPrototyping
{
	using namespace NDev::Types;

	struct FWindow
	{ 
		FSize Width, Height, X, Y, _UpdateCount;
		FBoolean bWait, bHold, bReconfigure;
		NDev::TPoint2D<FReal> Min, Max, Origin;
		FString Title;
		FReturn _ErrorNo;
		FPointer _State;

		static FWindow Default();

		static FVoid Display(const NDev::FDescriptor &, FWindow &);

		static FVoid _Make(const NDev::FDescriptor &, FWindow &);

		static FVoid _Update(const NDev::FDescriptor &, FWindow &);

		static FReturn Wait();

		static FPointer _Application;
		static char** _Arguments;
		static int _ArgumentCount;
	};


}


